/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** TCPClient
*/

#include "../../src/Client/Client.cpp"

class TCPClient {
public:
    TCPClient();
    ~TCPClient();
    bool Connect(const std::string& name ,const std::string& server_ip, int server_port);
    void Send(const std::string& message);
    std::string Receive();
    void Close();


    Client udpClient;

    Core core;
    std::string message = "";
    std::string received_message = "";
    std::size_t clientId = 0;
    bool gotRooms = false;

    std::string server_ip_;
    int server_port_;


private:

    asio::io_context io_context_;
    asio::ip::tcp::socket socket_;
};