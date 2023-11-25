#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream> // N'oubliez pas d'inclure l'en-tête pour stringstream
#include"folder.cpp"

char getLetterFromFileDesc(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        return ' ';
    }
    std::string line;
    std::string letter;
    while (std::getline(file, line)) {
        if (line.find("fileDesc :") != std::string::npos) {
            letter = line.substr(10); // Modifier l'index de début pour correspondre à la longueur de "fileDesc :"
            break;
        }
    }
    if (letter.empty()) {
        return ' ';
    }
    return letter[0];
}

std::string getTextureFromKyks(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return "";
    }
    std::string line;
    std::string letter;
    while (std::getline(file, line)) {
        if (line.find("texture :") != std::string::npos) {
            letter = line.substr(9,line.find("\n")); // Modifier l'index de début pour correspondre à la longueur de "fileDesc :"
            break;
        }
    }
    if (letter.empty()) {
        std::cerr << "Could not find 'texture :' in the file: " << fileName << std::endl;
        return "";
    }
    return letter.substr(4);
}

sf::IntRect getRectFromKyks(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return sf::IntRect();
    }
    std::string line;
    std::string rect;
    while (std::getline(file, line)) {
        if (line.find("rect :") != std::string::npos) {
            rect = line.substr(6); // Modifier l'index de début pour correspondre à la longueur de "rect :"
            break;
        }
    }
    if (rect.empty()) {
        std::cerr << "Could not find 'rect :' in the file: " << fileName << std::endl;
        return sf::IntRect();
    }

    // Supprimer les caractères inutiles
    rect.erase(std::remove(rect.begin(), rect.end(), '{'), rect.end());
    rect.erase(std::remove(rect.begin(), rect.end(), '}'), rect.end());

    std::stringstream ss(rect);
        std::string token;
        std::vector<int> values;
        while (std::getline(ss, token, ',')) {
            try {
                values.push_back(std::stoi(token));
            } catch (const std::invalid_argument &ia) {
                std::cerr << "Invalid argument: " << ia.what() << std::endl;
                return sf::IntRect();
            }
        }

    // Vérifier si nous avons le nombre attendu de valeurs
    if (values.size() != 4) {
        std::cerr << "Invalid number of values in rect: " << values.size() << std::endl;
        return sf::IntRect();
    }

    // Retourner sf::IntRect avec les valeurs extraites
    return sf::IntRect(values[0], values[2], values[1], values[3]);
}

class Test {
    public :
    char letterToprint;
    std::string filename;
};

int main(int ac,char **av)
{
    if(ac  != 2) {
        std::cout << "Not the right amount of arguments\n";
        exit(84);
    }
    sf::RectangleShape backgroundSquareShape;
    backgroundSquareShape.setSize(sf::Vector2f(100, 100)); // Taille des carrés de fond
    backgroundSquareShape.setFillColor(sf::Color::Transparent);
    backgroundSquareShape.setOutlineThickness(1);
    backgroundSquareShape.setOutlineColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game Editor");

    sf::Texture backgroundTexture;
    sf::Texture backgroundSquare;
    // sf::RectangleShape rect;

    if (!backgroundTexture.loadFromFile("../assets/space.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    if (!backgroundSquare.loadFromFile("../assets/carre.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    sf::Sprite background;
    sf::Sprite square;

    background.setTexture(backgroundTexture);
    background.setScale(
        float(window.getSize().x) / background.getLocalBounds().width,
        float(window.getSize().y) / background.getLocalBounds().height
    );

    square.setScale(1.3,1.6);

    square.setTexture(backgroundSquare);

    std::map<int, std::vector<std::pair<int, char>>> positionsMap;
    bool isDrawing = false;
    bool wasMouseClicked = false;
    bool isClickIndicatorVisible = false;
    char letterToPrint = ' ';
    std::vector<std::string> test = listFilesInFolder("../entities");
    for (int i = 0; i != test.size(); i++)
        test.at(i) = "../entities/" + test.at(i);
    std::string fileName = "../entities/obstacle.kyks";
    letterToPrint = getLetterFromFileDesc(fileName);

    std::map<char, sf::Texture> textureMap;
    std::map<char, sf::IntRect> rectMap;


    for (const auto &fileName : test) {
        char letter = getLetterFromFileDesc(fileName);
        if (letter != ' ') {
            std::string textureName = "../" + getTextureFromKyks(fileName);
            sf::Texture texture;
            texture.loadFromFile(textureName);
            textureMap[letter] = texture;

            sf::IntRect rect = getRectFromKyks(fileName);
            rectMap[letter] = rect;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDrawing = true;
                    int posX = event.mouseButton.x / 100;
                    int posY = event.mouseButton.y / 100;
                    if (!positionsMap[posY].empty())
                    {
                        if (posX < positionsMap[posY].back().first)
                        {
                            positionsMap[posY].insert(positionsMap[posY].begin(), std::make_pair(posX, letterToPrint));
                        }
                        else
                        {
                            positionsMap[posY].push_back(std::make_pair(posX, letterToPrint));
                        }
                    }
                    else
                    {
                        positionsMap[posY].push_back(std::make_pair(posX, letterToPrint));
                    }
                    wasMouseClicked = true;
                    isClickIndicatorVisible = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDrawing = false;
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S && wasMouseClicked)
                {
                    std::string file = av[1];
                    std::ofstream outputFile("../maps/" + file);
                    if (outputFile.is_open())
                    {
                        for (const auto &pos : positionsMap)
                        {
                            for (int i = 0; i < pos.first; i++)
                            {
                                outputFile << "\n";
                            }
                            for (const auto &p : pos.second)
                            {
                                for (int i = 0; i < p.first; i++)
                                {
                                    outputFile << "   ";
                                }
                                outputFile << p.second;
                            }
                        }
                        outputFile.close();
                        std::cout << "Map saved to map.txt" << std::endl;
                    }
                    else
                    {
                        std::cerr << "Unable to open file!" << std::endl;
                    }
                }
                else
                {
                    letterToPrint = (char)(event.key.code + 'a');
                    std::cout << "test : " << letterToPrint << std::endl;
                    for (int i = 0; i != test.size(); i++)
                    {
                        if (getLetterFromFileDesc(test.at(i)) != ' ')
                            std::cout << getLetterFromFileDesc(test.at(i)) << " \"" << letterToPrint << "\"" << std::endl;
                        if (letterToPrint == getLetterFromFileDesc(test.at(i)))
                        {
                            fileName = test.at(i);
                            std::cout << fileName;
                        }
                    }
                    if (textureMap.find(letterToPrint) == textureMap.end()) {
                        std::string textureName = "../"  + getTextureFromKyks(fileName);
                        sf::Texture texture;
                        texture.loadFromFile(textureName);
                        textureMap[letterToPrint] = texture;
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!isDrawing && wasMouseClicked)
            {
                wasMouseClicked = false;
            }
        }

        window.clear(sf::Color::White);

                window.draw(background);
                // window.draw(square);

        // Dessiner les carrés de fond
        for (int y = 0; y < 6; y++) // 6 lignes
        {
            for (int x = 0; x < 8; x++) // 8 colonnes
            {
                backgroundSquareShape.setPosition(x * 100, y * 100);
                window.draw(backgroundSquareShape);
            }
        }


        for (const auto &pos : positionsMap)
        {
            for (const auto &p : pos.second)
            {
                sf::Sprite sprite;
                if (textureMap.find(p.second) != textureMap.end()) {
                    sprite.setTexture(textureMap[p.second]);
                    sprite.setScale(0.10f, 0.10f); // Réduire la taille du sprite à 25% de sa taille d'origine
                }
                if (rectMap.find(p.second) != rectMap.end()) {
                    sprite.setTextureRect(rectMap[p.second]);
                }
                sprite.setPosition(p.first * 100, pos.first * 100);
                sprite.setScale(1, 1); // Rétablir l'échelle de la position du sprite
                window.draw(sprite);
            }
        }
        window.display();
    }
    return 0;
}
                