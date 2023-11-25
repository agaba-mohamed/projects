/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#include"../../src/Entity/Entity.cpp"

class SpawningSystem {
    public:
        SpawningSystem(){}
        ~SpawningSystem(){}
        void spawn(std::vector<std::unique_ptr<Entity>> *entities,std::string mess) {
            if(mess.size() == 0)
                return;
                int number = mess.at(0) - '0';
            if(mess.substr(3,8) == "shoot") {
                Entity test(entities->size(),entities->at(number)->getPos()->x,entities->at(number)->getPos()->x,"bullet");
                std::unique_ptr<Entity> testPtr = std::make_unique<Entity>(test);
                entities->push_back(std::move(testPtr));            }
            // for (int i = 0;i != players->size();i++) {
            //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //         if(players->at(i)->bullets.size() == 0 || players->at(i)->pos.x - players->at(i)->bullets.front().pos.x > 20) {
            //             players->at(i)->health.isShooting = true;
            //             players->at(i)->bullets.push_back(bullets);
            //         }
            //     }
            // }
        }

        // void spawnEnemy(std::vector<std::unique_ptr<Entity>> *entities) {
        //     std::ifstream inputFile("../map/map1.txt");

        //     if (!inputFile.is_open()) {
        //         std::cerr << "Error: Unable to open the file." << std::endl;
        //     }

        //     std::vector<std::string> lines;
        //     std::string line;

        //     while (std::getline(inputFile, line)) {
        //         lines.push_back(line);
        //     }

        //     inputFile.close();
        //         for (int i = 0; i < lines.size(); ++i) {
        //             for (int j = 0; j < lines[i].size(); ++j) {
        //                 if (lines[i][j] == 'x') {
        //                     core->createEnemy(core->entities_number, j, i); // Pass the position (x, y)
        //                 }
        //             }
        //     }
        // }
    protected:
    private:
};
