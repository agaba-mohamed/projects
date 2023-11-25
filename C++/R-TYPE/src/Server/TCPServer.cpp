/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** TCPServer
*/

#include "../../includes/Server/TCPServer.hpp"



TCPServer::TCPServer(std::size_t port) : acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    rooms[0].roomInfo = "Room 0: Null 0 0 0";
    rooms[1].roomInfo = "Room 1: Null 0 0 0";
    rooms[2].roomInfo = "Room 2: Null 0 0 0";
    rooms[3].roomInfo = "Room 3: Null 0 0 0";
    rooms[4].roomInfo = "Room 4: Null 0 0 0";
    rooms[5].roomInfo = "Room 5: Null 0 0 0";
    rooms[6].roomInfo = "Room 6: Null 0 0 0";
    rooms[7].roomInfo = "Room 7: Null 0 0 0";
    rooms[8].roomInfo = "Room 8: Null 0 0 0";
    std::cout << "TCP Server is listening on port " << port << std::endl;
    this->port = port;
    StartAccept();
    io_context.run();
}

TCPServer::~TCPServer()
{
    // Destructor implementation, if needed
}

void TCPServer::StartAccept()
{
    auto newSocket = std::make_shared<asio::ip::tcp::socket>(io_context);
    acceptor.async_accept(*newSocket, [this, newSocket](const asio::error_code& error) {
        if (!error) {
            std::cout << "Client connected: " << newSocket->remote_endpoint() << std::endl;
            auto newPlayer = std::make_shared<Player>(newSocket, "");
            clients.push_back(newPlayer);
            Send(newSocket,"220");
            StartRead(newSocket);
        } else {
            Send(newSocket,"401");
        }
        StartAccept();
    });
}

void TCPServer::StartRead(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    asio::async_read_until(*socket, buffer, '\n', [this, socket](const asio::error_code& error, std::size_t bytes_transferred) {
        if (!error) {
            std::istream input_stream(&buffer);
            std::string data;
            std::getline(input_stream, data);
            if (data.find("GetRoom") == std::string::npos)
                std::cout << "Received data: " << data << std::endl;
            HandleReceivedData(socket, data);
            StartRead(socket);
        } else {
            RemoveClient(socket);
        }
    });
}

void TCPServer::Send(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& message)
{
    asio::async_write(*socket, asio::buffer(message + "\n"),
                     [this, socket](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error) {
            RemoveClient(socket);
        }
    });
}

void TCPServer::SendToAllClients(const std::string& message)
{
    for (const auto& client : clients) {
        Send(client->_socket, message);
        std::cout << "Send to client" << std::endl;
    }
}

void TCPServer::RemoveClient(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->_socket == socket) {
            std::cout << "Client disconnected: " << (*socket).remote_endpoint() << std::endl;
            clients.erase(it);
            break;
        }
    }
}

void TCPServer::HandleReceivedData(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& data)
{
    if (data == "GETROOMS") {
        std::string message("");
        for (std::size_t i = 0; i < 9; i++) {
            message.append(rooms[i].roomInfo + "/");
        }
        std::cout << message << std::endl;
        Send(socket, "240:" + message);
    } else if (data.find("GETROOMPARTICIPANTS") != std::string::npos)  {
        std::istringstream iss(data);
        std::string identifier;
        std::string room;
        iss >> identifier >> room;
        std::string message("");
        for (std::size_t i = 0; i < rooms[std::stoi(room)].participants.size(); i++) {
            message.append(rooms[std::stoi(room)].participants[i] + "/");
        }
        Send(socket, "250:" + message);
    } else if (data.find("CREATEROOM") != std::string::npos) {
        bool createroom = true;
        std::string player;
        std::istringstream iss(data);
        std::string identifier;
        std::size_t IdRect;
        std::string name;
        std::string NombreJoueursActuels = "0";
        std::size_t difficulty, NombreJoueursMax;
        std::string map;

        iss >> identifier >> IdRect;
        if (iss.peek() == ':')
            iss.ignore();
        iss >> name >> difficulty >> NombreJoueursMax >> map;
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if (name.empty() || NombreJoueursActuels.empty() || difficulty < 1 || NombreJoueursMax < 1) {
                Send((*it)->_socket, "402\n");
                createroom = false;
            } else if ((*it)->_socket == socket) {
                player.assign((*it)->_name);
                Send((*it)->_socket, "260\n");
            } 
        }
        if (createroom) {
            rooms[IdRect].participants.push_back(player);
            std::string roomInfo("ROOM " + std::to_string(IdRect) + ": " + name + " " + std::to_string(difficulty) + " " + std::to_string(NombreJoueursMax) + " " + std::to_string(rooms[IdRect].participants.size()) + " " + map);
            rooms[IdRect].roomInfo.assign(roomInfo);
        }
    } else if (data.find("USER") != std::string::npos) {
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if ((*it)->_socket == socket) {
                std::istringstream iss(data);
                std::string identifier;
                std::string name;
                iss >> identifier >> name;
                it->get()->_name.assign(name);
                std::cout << "Client Paired: " << name << " "  << (*socket).remote_endpoint() << std::endl;
                Send((*it)->_socket, "230\n");
                break;
            }
        }
    } else if (data.find("JOIN") != std::string::npos) {
        std::istringstream iss(data);
        std::string identifier;
        std::string roomNumber;
        iss >> identifier >> roomNumber;
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if ((*it)->_socket == socket) {
                std::cout << "Client Joined Room" << roomNumber << ": " << (*it)->_name << " "  << (*socket).remote_endpoint() << std::endl;
                rooms[std::stoi(roomNumber)].participants.push_back((*it)->_name);
                Send((*it)->_socket, "270\n");
                break;
            }
        }
        size_t lastSpacePos = rooms[std::stoi(roomNumber)].roomInfo.rfind(' ');
        if (lastSpacePos != std::string::npos) {
            std::string nbOfPlayers = rooms[std::stoi(roomNumber)].roomInfo.substr(lastSpacePos - 1);
            std::cout << "nbOfPlayers: " << nbOfPlayers << std::endl;
            int nbPlayers = std::stoi(nbOfPlayers);
            nbPlayers++;
            std::string updatedNbPlayers = std::to_string(nbPlayers);
            size_t startPos = lastSpacePos - 1;
            size_t lengthToReplace = updatedNbPlayers.length();
            rooms[std::stoi(roomNumber)].roomInfo.replace(startPos, lengthToReplace, updatedNbPlayers);
        }
    } else if (data.find("LEAVE") != std::string::npos) {
        std::istringstream iss(data);
        std::string identifier;
        std::string roomNumber;
        iss >> identifier >> roomNumber;
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if ((*it)->_socket == socket) {
                std::cout << "Client Leave Room " << roomNumber << ": " << (*it)->_name << " " << (*socket).remote_endpoint() << std::endl;
                int roomIndex = std::stoi(roomNumber);
                auto participantIt = std::find(rooms[roomIndex].participants.begin(), rooms[roomIndex].participants.end(), (*it)->_name);
                if (participantIt != rooms[roomIndex].participants.end()) {
                    rooms[roomIndex].participants.erase(participantIt);
                }
                Send((*it)->_socket, "271\n");
                break;
            }
        }
        size_t lastSpacePos = rooms[std::stoi(roomNumber)].roomInfo.rfind(' ');
        if (lastSpacePos != std::string::npos) {
            std::string nbOfPlayers = rooms[std::stoi(roomNumber)].roomInfo.substr(lastSpacePos - 1);
            std::cout << "nbOfPlayers: " << nbOfPlayers << std::endl;
            int nbPlayers = std::stoi(nbOfPlayers);
            nbPlayers--;
            std::string updatedNbPlayers = std::to_string(nbPlayers);
            size_t startPos = lastSpacePos - 1;
            size_t lengthToReplace = updatedNbPlayers.length();
            rooms[std::stoi(roomNumber)].roomInfo.replace(startPos, lengthToReplace, updatedNbPlayers);
        }
    } else if ((data.find("START") != std::string::npos)) {
        std::istringstream iss(data);
        std::string identifier;
        std::string roomNumber;
        iss >> identifier >> roomNumber;
        for (std::size_t i = 0; i < rooms[std::stoi(roomNumber)].participants.size(); i++) {
            for (auto it = clients.begin(); it != clients.end(); ++it) {
                if ((*it)->_name == rooms[std::stoi(roomNumber)].participants[i]) {
                    Send((*it)->_socket, "280");
                }
            }

        }
        size_t lastSpacePos = rooms[std::stoi(roomNumber)].roomInfo.rfind(' ');
        std::string nbOfPlayersMax = rooms[std::stoi(roomNumber)].roomInfo.substr(lastSpacePos - 3);
        std::string map = rooms[std::stoi(roomNumber)].roomInfo.substr(lastSpacePos + 1, rooms[std::stoi(roomNumber)].roomInfo.length());
        int nbPlayersMax = std::stoi(nbOfPlayersMax);
        roomsServer.push_back(std::make_unique<Server>((this->port + std::stoi(roomNumber) + 1), nbPlayersMax, map));

    }
    // else {
    //     // Handle other cases or send a response to the client
    //     Send(socket, "Invalid command: " + data);
    // }
    // SendToAllClients(data);
}
