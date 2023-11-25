/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <functional>
#include "../../src/Core/Core.cpp"
std::mutex blockEntity;


class Server : public virtual RType {
public:
    Server(std::size_t port, std::size_t player_number, std::string map);
    ~Server();
    void send(std::string message, asio::ip::udp::endpoint clientEndpoint);
    void receive(const asio::error_code& error, std::size_t bytes_received, asio::ip::udp::socket& socket);
    void handleClients(asio::ip::udp::endpoint clientEndpoint);
    void handleCollision();
    void handleMovement();
    void handleEntity();
    void launchServer();

    Core core;
    std::string data;
    std::string dataToSend;
    std::string collision;
    std::string map;
    std::size_t port;
    std::size_t player_numbers;
    std::size_t enemy_numbers;
    std::vector<asio::ip::udp::endpoint> players_info;
    std::thread server_thread;
    std::thread entity_thread;
    std::thread client_thread;
    std::thread collision_thread;
    std::thread movement_thread;
    std::unique_ptr<asio::io_context> io_context;
    std::unique_ptr<asio::ip::udp::socket> socket;
    std::array<char, 1024> receive_buffer;
    asio::ip::udp::endpoint sender_endpoint;

protected:

private:

};

#endif /* !SERVER_HPP_ */