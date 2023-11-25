/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** CoreManager
*/

#include "../../includes/Core/CoreManager.hpp"

CoreManager::CoreManager(int ac, char **av)
{
    this->ac = ac;
    if (ac == 4) {
        name = av[1];
        ip = av[2];
        port = av[3];
    } else  {
        name = "Entrer votre pseudo";
        ip = "IP";
        port = "Port";
    }
    setVariables();
}

void CoreManager::run()
{
    client.core.backgroundMusic.setLoop(true);
    client.core.backgroundMusic.play();
    for (;client.core.win.isOpen();) {
        int aS = client.core.actualScreen;
        handleDisplay();
        if (aS == 0) {
            menuScreen();
        } else if (aS == 1) {
            lobbyScreen();
        } else if (aS == 3) {
            gameScreen();
        }
        client.core.win.display();
    }
    client.Close();
}

void CoreManager::setVariables()
{
    client.core.menu._inputText.setString(name);
    client.core.menu._inputIpText.setString(ip);
    client.core.menu._inputPortText.setString(port);
    client.core.menu._userInput = name;
    client.core.menu._userIpInput = ip;
    client.core.menu._userPortInput = port;
}

void CoreManager::handleDisplay()
{
    client.core.win.clear();
    client.core.menu.clockGestion(client.core.backgroundSprite1, client.core.backgroundSprite2, client.core.actualScreen);
    client.core.menu.actualiseVariables();
    client.core.displayAll();
}

void CoreManager::handleCoreEvent()
{
    sf::FloatRect pseudoBounds = client.core.menu._inputText.getGlobalBounds();
    sf::FloatRect playBounds = client.core.menu._playText.getGlobalBounds();
    sf::FloatRect ipBounds = client.core.menu._inputIpText.getGlobalBounds();
    sf::FloatRect portBounds = client.core.menu._inputPortText.getGlobalBounds();
    if (pseudoBounds.contains(sf::Vector2f(mousePosition))) {
        client.core.menu._isTyping = true;
        client.core.menu._isTypingPseudo = true;
        client.core.menu._isTypingIp = false;
        client.core.menu._isTypingPort = false;
    } else if (ipBounds.contains(sf::Vector2f(mousePosition))) {
        client.core.menu._isTyping = true;
        client.core.menu._isTypingPseudo = false;
        client.core.menu._isTypingIp = true;
        client.core.menu._isTypingPort = false;
    } else if (portBounds.contains(sf::Vector2f(mousePosition))) {
        client.core.menu._isTyping = true;
        client.core.menu._isTypingPseudo = false;
        client.core.menu._isTypingIp = false;
        client.core.menu._isTypingPort = true;
    } else if (playBounds.contains(sf::Vector2f(mousePosition))) {
        if (!client.core.menu._userInput.empty() && !client.core.menu._userIpInput.empty() && !client.core.menu._userPortInput.empty()) {
            if (client.Connect(client.core.menu._userInput ,client.core.menu._userIpInput, std::stoi(client.core.menu._userPortInput))) {
                client.core.actualScreen = 1;
                client.core.menu._menuPage = 1;
            }
        }
    } else {
        client.core.menu._isTyping = false;
        client.core.menu._isTypingPseudo = false;
        client.core.menu._isTypingIp = false;
        client.core.menu._isTypingPort = false;
    }
}

void CoreManager::menuScreen()
{
    mousePosition = sf::Mouse::getPosition(client.core.win);
    while (client.core.win.pollEvent(client.core.windowEvent)) {
        if (client.core.windowEvent.type == sf::Event::Closed) {
            client.core.win.close();
        }
        if (client.core.windowEvent.type == sf::Event::TextEntered && client.core.menu._isTyping == true) {
            client.core.menu.getInput(client.core.windowEvent);
        } else if (client.core.windowEvent.type == sf::Event::MouseButtonPressed) {
            handleCoreEvent();
        } else if (client.core.windowEvent.type == sf::Event::KeyPressed && (client.core.windowEvent.key.code == sf::Keyboard::Escape || client.core.windowEvent.key.code == sf::Keyboard::Enter)) {
            client.core.menu._isTyping = false;
            client.core.menu._isTypingPseudo = false;
            client.core.menu._isTypingIp = false;
            client.core.menu._isTypingPort = false;
        }
    }
    client.core.menu.assignVariables(client.core.win);
    client.core.menu.drawVariables(client.core.win, client.core.roomCreating);
}

void CoreManager::getStart()
{
    if (client.received_message.find("280") != std::string::npos) {
        client.core.actualScreen = 3;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client.core.backgroundMusicBuffer.loadFromFile("../assets/sounds/music.ogg");
        client.core.backgroundText.loadFromFile("../assets/background.png");
        client.core.backgroundSprite1.setTexture(client.core.backgroundText);
        client.core.backgroundSprite2.setTexture(client.core.backgroundText);
        client.core.backgroundSprite1.setPosition(0, 0);
        client.core.backgroundSprite2.setPosition(2159, 0);
        client.core.backgroundMusic.setBuffer(client.core.backgroundMusicBuffer);
        client.core.backgroundMusic.setLoop(true);
        client.core.backgroundMusic.play();
        client.udpClient.connect(client.server_ip_, client.server_port_ + client.core.roomCreating + 1);
        client.udpClient.startReceive();
    }

}

void CoreManager::getRooms()
{
    client.Send("GETROOMS");
    client.received_message.assign(client.Receive());
    getStart();
    if (client.received_message.find("280") == std::string::npos)
        client.core.menu.receiveLobbies(client.received_message);
}

void CoreManager::getRoom()
{
    client.Send("GETROOMPARTICIPANTS " + std::to_string(client.core.roomCreating));
    client.received_message.assign(client.Receive());
    getStart();
    if (client.received_message.find("280") == std::string::npos)
        client.core.menu.receiveParticipants(client.received_message);
    
}

void CoreManager::lobbyScreen()
{

    getRooms();
    if (client.core.menu._isNewGameOpen && client.core.actualScreen == 1)
        getRoom();
    client.received_message.assign("");
    sf::Vector2i mousePosition = sf::Mouse::getPosition(client.core.win);
    while (client.core.win.pollEvent(client.core.windowEvent))
        client.core.eventGestion(sf::Vector2f(mousePosition), client.message);
    if (client.message != "") {
        client.Send(client.message);
        if (client.message.find("CREATEROOM") == std::string::npos || client.message.find("JOIN") == std::string::npos || client.message.find("LEAVE") == std::string::npos) {
            client.received_message.assign(client.Receive());
            std::cout << client.received_message << std::endl;
        }
        client.message.assign("");
        getStart();
    }
    client.core.menu.assignVariables(client.core.win);
    client.core.menu.drawVariables(client.core.win, client.core.roomCreating);
    client.core.settings.settingsGestion(client.core.win);
    client.core.settings.drawSettings(client.core.win);
}

void CoreManager::gameScreen()
{
    if (!client.udpClient.core.entities.empty() && client.udpClient.clientId <= client.udpClient.core.entities.size()) {
        client.udpClient.message = (client.udpClient.core.entities.at(0).get())->handleEvents(client.core.win, client.core.windowEvent);
    }      
    for (auto &entity : client.udpClient.core.entities) {
        if (entity->getType() != "player")
            entity->getTimer()->startTimer();
        if (entity->getType() == "basic_enemy" && entity->getTimer()->checkTimer(0.0001)) {
            entity->predictEnemyMovement();
            entity->getTimer()->ResetTimer();
        }
        if (entity->getType() == "bullet" && entity->getTimer()->checkTimer(0.0001)) {
            entity->predictBulletMovement();
            entity->getTimer()->ResetTimer();
        }
    
    }

    client.udpClient.core.handlePackage(client.udpClient.received_message, client.udpClient.clientId);
    client.udpClient.core.hitbox.handleCollision(client.udpClient.core.entities, client.udpClient.received_message);
    client.udpClient.core.render.render(client.udpClient.core.entities, client.core.win);
    if (client.udpClient.message != "")
        client.udpClient.send();
}


CoreManager::~CoreManager()
{
}
