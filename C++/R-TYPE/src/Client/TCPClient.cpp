/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** TCPClient
*/

#include "../../includes/Client/TCPClient.hpp"

TCPClient::TCPClient() : io_context_(), socket_(io_context_), core(true)
{
}

bool TCPClient::Connect(const std::string& name ,const std::string& server_ip, int server_port)
{
    try {
        this->server_ip_ = server_ip;
        this->server_port_ = server_port;
        asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string(server_ip_), server_port_);
        socket_.connect(endpoint);
        received_message = Receive();
        std::cout << received_message << ": Connected to server at " << server_ip_ << ":" << server_port_ << std::endl;
        Send("USER: " + name);
        received_message = Receive();
        std::cout << received_message << ": Logged in as USER  " << name << std::endl;
        return true;
    } catch (std::exception& e) {
        std::cerr << "401 Connection error: " << e.what() << std::endl;
        return false;
    }
}

void TCPClient::Send(const std::string& message)
{
    try {
        asio::write(socket_, asio::buffer(message + '\n'));
    } catch (std::exception& e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}


std::string TCPClient::Receive()
{
    try {
        asio::streambuf receive_buffer;
        asio::read_until(socket_, receive_buffer, '\n');
        std::istream response_stream(&receive_buffer);
        std::string response;
        std::getline(response_stream, response);
        return response;
    } catch (std::exception& e) {
        std::cerr << "Receive error: " << e.what() << std::endl;
        return "";
    }
}

void TCPClient::Close()
{
    socket_.close();
}

TCPClient::~TCPClient()
{
    Close();
}
