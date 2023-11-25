/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** CoreManager
*/

#include"../../src/Client/TCPClient.cpp"

#ifndef COREMANAGER_HPP_
#define COREMANAGER_HPP_

class CoreManager {
    public:
        CoreManager(int ac, char **av);
        ~CoreManager();

        void run();
        void setVariables();
        void handleDisplay();
        void handleCoreEvent();
        void menuScreen();
        void lobbyScreen();
        void gameScreen();
        void getStart();
        void getRooms();
        void getRoom();

        std::size_t ac;
        TCPClient client;
        std::string name;
        std::string ip;
        std::string port;
        sf::Vector2i mousePosition;
        std::thread movement_thread;

    protected:
    private:
};

#endif /* !COREMANAGER_HPP_ */
