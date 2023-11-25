/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Core
*/

#include "../../includes/Core/Core.hpp"

std::string previous_data = "";

Core::Core(bool screen)
{
    if (screen) {
        desktopMode = sf::VideoMode::getDesktopMode();
        win.create(sf::VideoMode(1920, 1080), "R_TYPE");
        win.setFramerateLimit(60);
        _middlegroundTexture.loadFromFile("../assets/middleground.png");
        backgroundText.loadFromFile("../assets/space.jpg");
        backgroundSprite1.setTexture(backgroundText);
        backgroundSprite2.setTexture(backgroundText);
        _middlegroundSprite.setTexture(_middlegroundTexture);
        backgroundSprite1.setPosition(0, 0);
        backgroundSprite2.setPosition(2159, 0);
        _middlegroundSprite.setPosition(0, 0);
        backgroundSprite1.setScale(1, 0.95);
        backgroundSprite2.setScale(1, 0.95);
        _middlegroundSprite.setScale(1, 0.95);
        actualScreen = 0;
        isSettingsOpen = false;
        backgroundMusicBuffer.loadFromFile("../assets/sounds/menu.ogg");
        backgroundMusic.setBuffer(backgroundMusicBuffer);
    }
}

Core::~Core()
{
    win.close();
}

std::string Core:: handlePackage(std::string data, std::size_t index)
{
    if (data.find("shoot") != std::string::npos) {
        if (previous_data == data) {
            previous_data = data;
            return "";
        }
        previous_data = data;
    }
    for (auto& entity : entities) {
        // if (data == "Id: " + std::to_string(entity->getId()) + ": shoot")
        if (entity->getId() == index) {
            continue;
        }

        size_t idPos = data.find("Id: " + std::to_string(entity->getId()) + ":");
        if (idPos == 0) {
            size_t xPos = data.find("x:");
            size_t yPos = data.find("y:");

            if (xPos != std::string::npos && yPos != std::string::npos) {
                try {
                    int newPositionX, newPositionY;
                    std::istringstream xStream(data.substr(xPos + 2, yPos - (xPos + 2)));
                    std::istringstream yStream(data.substr(yPos + 2, data.find("type") - 2));
                    xStream >> newPositionX;
                    yStream >> newPositionY;
                    if (xStream && yStream) {
                        entity->setPos(newPositionX, newPositionY);
                        entity->setHitbox(newPositionX, newPositionY);
                    } else {
                        std::cerr << "Error: Invalid integer value in data." << std::endl;
                    }
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: Invalid integer value in data." << std::endl;
                }
            } else {
                std::cerr << "Error: 'x' and 'y' positions not found in data." << std::endl;
            }
        }
    }

    return data;
}

void Core::displayAll()
{
    win.clear();
    menu.clockGestion(backgroundSprite1, backgroundSprite2, actualScreen);
    menu.actualiseVariables();
    win.draw(backgroundSprite1);
    win.draw(backgroundSprite2);
    if (actualScreen == 3) {
        win.draw(_middlegroundSprite);
        if (menu._second2 > 0.001) {
            sf::Vector2f posMGS = _middlegroundSprite.getPosition();
            if (posMGS.x < 2250)
                _middlegroundSprite.move(sf::Vector2f(-1.5f, 0.0f));
        }
    }
}

void Core::createEntity(std::size_t id, float x, float y, std::string type)
{
    if(type == "player") {
        player_number++;
        entities.push_back(std::make_unique<Entity>(id, x, y, type, player_number));
    } else {
        entities.push_back(std::make_unique<Entity>(id, x, y, type));
    }
    entities_number += 1;
}

void Core::eventGestion(sf::Vector2f mousePosition, std::string &message)
{
    if (windowEvent.type == sf::Event::Closed) {
        win.close();
    } else if (windowEvent.type == sf::Event::MouseButtonPressed) {
        closePopUp(mousePosition, message);
        openSettings(mousePosition);
        if (isSettingsOpen) {
            logout(mousePosition);
        } else if (menu._isNewGameOpen) {
            inputGameName(mousePosition);
            selectLevel(mousePosition);
            selectNbPlayers(mousePosition);
            changeMap(mousePosition);
            if (menu._isNewGameOpen && menu._rectData[roomCreating].isNotEmpty) {
                message = launchGame(mousePosition);
            } else {
                message = createRoom(mousePosition);
            }
        } else {
            createGameButton(mousePosition, message);
        }
    } else if (windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == sf::Keyboard::Escape) {
        if (menu._isTyping) {
            menu._isTyping = false;
        } else {
            settings.isSettingsOpen = false;
            menu._isSettingsOpen = false;
            isSettingsOpen = false;
            if (menu._isNewGameOpen && menu._rectData[roomCreating].isNotEmpty)
                message = "LEAVE " + std::to_string(roomCreating);
            menu._isNewGameOpen = false;
            menu._userInputGameName.clear();
            menu._newGameValues.resetValues();

        }
    } else if (windowEvent.type == sf::Event::TextEntered && menu._isTyping) {
        menu.getInput(windowEvent);
    }
}

void Core::closePopUp(sf::Vector2f mousePosition, std::string &message)
{
    /* GESTION FERMETURE POP UP */
    sf::FloatRect popUpBounds = settings.backgroundRect.getGlobalBounds();
    if (!popUpBounds.contains(mousePosition) && (isSettingsOpen || menu._isNewGameOpen)) {
        settings.isSettingsOpen = false;
        menu._isSettingsOpen = false;
        isSettingsOpen = false;
        if (menu._isNewGameOpen && menu._rectData[roomCreating].isNotEmpty)
            message = "Leave " + std::to_string(roomCreating);
        menu._isNewGameOpen = false;
        menu._userInputGameName.clear();
        menu._newGameValues.resetValues();
    }
}

void Core::openSettings(sf::Vector2f mousePosition)
{
    /* GESTION BOUTON OUVERTURE PARAMETRES */
    sf::FloatRect settingsIconBounds = settings.settingsIconSprite.getGlobalBounds();
    if (settingsIconBounds.contains(mousePosition)) {
        settings.isSettingsOpen = true;
        menu._isSettingsOpen = true;
        isSettingsOpen = true;
    }
}

void Core::logout(sf::Vector2f mousePosition)
{
    /* GESTION BOUTON SE DECONNECTER */
    sf::FloatRect logoutBounds = settings.logoutText.getGlobalBounds();
    if (logoutBounds.contains(mousePosition)) {
        settings.isSettingsOpen = false;
        menu._isSettingsOpen = false;
        isSettingsOpen = false;
        actualScreen = 0;
        menu._menuPage = 0;
    }
}

void Core::createGameButton(sf::Vector2f mousePosition, std::string &message)
{
    /* GESTION OUVERTURE NOUVELLE GAME */
    for (int i = 0; i < 9; i++) {
        sf::FloatRect rectBounds = menu._rectSlots[i].getGlobalBounds();
        if (rectBounds.contains(mousePosition) && !settings.isSettingsOpen && !menu._isNewGameOpen ) {
            menu._isNewGameOpen = true;
            roomCreating = i;
            if (menu._rectData[i].isNotEmpty) {
                message.assign("JOIN " + std::to_string(i));
            }
        }
    }
}

void Core::inputGameName(sf::Vector2f mousePosition)
{
    /* CLICK INPUT NOM DE LA GAME */
    sf::FloatRect pseudoBounds = menu._inputGameName.getGlobalBounds();
    if (pseudoBounds.contains(mousePosition)) {
        menu._isTyping = true;
    }
}

void Core::selectLevel(sf::Vector2f mousePosition)
{
    sf::FloatRect lvl1TxtB = menu._level1Text.getGlobalBounds();
    sf::FloatRect lvl2TxtB = menu._level2Text.getGlobalBounds();
    sf::FloatRect lvl3TxtB = menu._level3Text.getGlobalBounds();

    if (lvl1TxtB.contains(mousePosition)) {
        menu._newGameValues.level = 1;
    } else if (lvl2TxtB.contains(mousePosition)) {
        menu._newGameValues.level = 2;
    } else if (lvl3TxtB.contains(mousePosition)) {
        menu._newGameValues.level = 3;
    }
}

void Core::selectNbPlayers(sf::Vector2f mousePosition)
{
    sf::FloatRect p1TxtB = menu._p1Text.getGlobalBounds();
    sf::FloatRect p2TxtB = menu._p2Text.getGlobalBounds();
    sf::FloatRect p3TxtB = menu._p3Text.getGlobalBounds();
    sf::FloatRect p4TxtB = menu._p4Text.getGlobalBounds();

    if (p1TxtB.contains(mousePosition)) {
        menu._newGameValues.players = 1;
    } else if (p2TxtB.contains(mousePosition)) {
        menu._newGameValues.players = 2;
    } else if (p3TxtB.contains(mousePosition)) {
        menu._newGameValues.players = 3;
    } else if (p4TxtB.contains(mousePosition)) {
        menu._newGameValues.players = 4;
    }
}

void Core::changeMap(sf::Vector2f mousePosition)
{
    sf::FloatRect next = menu._nextMapArrow.getGlobalBounds();
    sf::FloatRect prev = menu._prevMapArrow.getGlobalBounds();

    if (next.contains(mousePosition)) {
        if (menu._newGameValues.i == menu._newGameValues.iMax - 1)
            menu._newGameValues.i = 0;
        else
            menu._newGameValues.i += 1;
        menu._mapSelectedText.setString(menu._newGameValues.mapList[menu._newGameValues.i]);
        menu._newGameValues.map = menu._newGameValues.mapList[menu._newGameValues.i];
    } else if (prev.contains(mousePosition)) {
        if (menu._newGameValues.i == 0)
            menu._newGameValues.i = menu._newGameValues.iMax - 1;
        else
            menu._newGameValues.i -= 1;
        menu._mapSelectedText.setString(menu._newGameValues.mapList[menu._newGameValues.i]);
        menu._newGameValues.map = menu._newGameValues.mapList[menu._newGameValues.i];
    }
}

std::string Core::createRoom(sf::Vector2f mousePosition)
{
    sf::FloatRect startButton = menu._startNewGame.getGlobalBounds();

    if (startButton.contains(mousePosition)) {
        std::string room("CREATEROOM " + std::to_string(roomCreating) + ": " + menu._newGameValues.name + " " + std::to_string(menu._newGameValues.level) + " " + std::to_string(menu._newGameValues.players) + " " + menu._newGameValues.map);
        return room;
    }
    return "";
}

std::string Core::launchGame(sf::Vector2f mousePosition)
{
    sf::FloatRect launchButton = menu._startGame.getGlobalBounds();

    if (launchButton.contains(mousePosition)) {
        std::size_t playersConnected = menu.participants.size();
        if (playersConnected == menu._lobbiesPlayersMax[roomCreating]) {
            std::string room("START " + std::to_string(roomCreating));
            return room;
        }
    }
    return "";
}