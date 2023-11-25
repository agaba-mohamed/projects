/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: Ubuntu]
** File description:
** udpclient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "../../src/Core/Core.cpp"

class Client : public virtual RType {
    public:
        Client();
        ~Client();
        void send();
        void parseId(std::string received_message);
        void startReceive();
        void stopReceive();
        int connect(std::string ip, unsigned short server_port);

        Core core;
        bool connected = false;
        std::size_t clientId = 0;
        std::string message = "";
        std::string received_message = "";
        std::vector<std::string> newExplosion;

    protected:

    private:
        asio::io_context io_context;
        asio::ip::udp::socket socket{io_context};
        asio::ip::udp::endpoint server_endpoint;
        std::thread receive_thread;
};


#endif /* !UDPCLIENT_HPP_ */
