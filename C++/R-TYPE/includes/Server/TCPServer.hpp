/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** TCPServer
*/

#include "../../src/Server/Server.cpp"

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

class Player {
    public:
    Player(std::shared_ptr<asio::ip::tcp::socket> socket, std::string name): _socket(socket),  _name(name) {};
    ~Player() {};


    std::shared_ptr<asio::ip::tcp::socket> _socket;
    std::string _name;
};

class Room {
    public:
        std::string roomInfo;
        std::vector<std::string> participants;
};

class TCPServer {
    public:
        TCPServer(std::size_t port);
        ~TCPServer();

    private:
        void StartAccept();
        void StartRead(std::shared_ptr<asio::ip::tcp::socket> socket);
        void Send(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& message);
        void SendToAllClients(const std::string& message);
        void RemoveClient(std::shared_ptr<asio::ip::tcp::socket> socket);
        void HandleReceivedData(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& data);

        std::size_t port;
        asio::io_context io_context;
        asio::ip::tcp::acceptor acceptor;
        asio::streambuf buffer;
        std::vector<std::shared_ptr<Player>> clients;
        Room rooms[9];
        std::vector<std::vector<std::string>> roomsParticipants;
        std::vector<std::unique_ptr<Server>> roomsServer;
};

#endif /* !TCPSERVER_HPP_ */
