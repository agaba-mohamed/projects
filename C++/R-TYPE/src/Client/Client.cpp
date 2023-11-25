/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** UDPClient
*/

#include "../../includes/Client/Client.hpp"

std::string last_message = "";

Client::Client(): core(false)
{
}

Client::~Client()
{
    socket.close();
}

int Client::connect(std::string ip, unsigned short server_port)
{
    core.screen = true;
    std::cout << ip << " " << server_port << std::endl;
    server_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(ip), server_port);
    socket.open(asio::ip::udp::v4());
    this->message = "Hello je suis NLE";
    this->send();
    this->message.clear();
    return (1);
}

void Client::startReceive()
{
    receive_thread = std::thread([this]() {
        while (true) {
            std::array<char, 1024> receive_buffer;
            asio::ip::udp::endpoint sender_endpoint;

            size_t bytes_received = socket.receive_from(asio::buffer(receive_buffer), sender_endpoint);

            if (bytes_received > 0) {
                HuffmanDecoder decoder;
                size_t extractedTreeSize = 0;
                for (size_t i = 0; i < sizeof(size_t); ++i) 
                    extractedTreeSize |= static_cast<size_t>(receive_buffer[i]) << (i * 8);
                std::vector<uint8_t> serializedTreePart(receive_buffer.begin() + sizeof(size_t), receive_buffer.begin() + sizeof(size_t) + extractedTreeSize);
                std::string encodedTextPart(receive_buffer.begin() + sizeof(size_t) + extractedTreeSize, receive_buffer.begin() + bytes_received);
                decoder.deserializeTree(serializedTreePart);
                std::string decodedText = decoder.decode(encodedTextPart);
                received_message.assign(decodedText);
                if (received_message.find("collision") != std::string::npos)
                    newExplosion = core.hitbox.handleCollision(core.entities, received_message);
                if (!newExplosion.empty()) {
                    core.createEntity(core.entities_number + 100, std::stoi(newExplosion.at(0)), std::stoi(newExplosion.at(1)), newExplosion.at(2));
                    newExplosion.clear();
                }
                core.handlePackage(received_message, clientId);
                parseId(received_message);
            }
        }
    });
}

void Client::stopReceive()
{
    receive_thread.join();
}

void Client::parseId(std::string received_message)
{
    std::string idLabel = "Id:";
    int idValue = 0;
    size_t labelPos = received_message.find(idLabel);
    if (last_message == received_message) {
        last_message = received_message;
        return;
    }
    last_message = received_message;
    if (labelPos != std::string::npos) {
        std::string valueSubstring = received_message.substr(labelPos + idLabel.length());

        std::stringstream ss(valueSubstring);
        ss >> idValue;
        if (!ss.fail()) {
            int x = 0;
            int y = 0;
            std::string type;

            size_t xPos = valueSubstring.find("x:");
            if (xPos != std::string::npos) {
                std::string xSubstring = valueSubstring.substr(xPos + 2);
                std::stringstream xss(xSubstring);
                xss >> x;
            }

            size_t yPos = valueSubstring.find("y:");
            if (yPos != std::string::npos) {
                std::string ySubstring = valueSubstring.substr(yPos + 2);
                std::stringstream yss(ySubstring);
                yss >> y;
            }

            size_t typePos = valueSubstring.find("type:");
            if (typePos != std::string::npos)
                type = valueSubstring.substr(typePos + 6);

            if (!connected) {
                this->clientId = idValue ;
                this->connected = true;
                std::cout << "Connected" << std::endl;
            }
            for (auto &entity : core.entities)
                if (entity->getId() == idValue && entity)
                    return;
            core.createEntity(idValue , x, y, type);
        } else {
            std::cerr << "Failed to parse Id value." << std::endl;
        }
    }
}


void Client::send() 
{
    HuffmanEncoder encoder(message);
    std::vector<uint8_t> serializedTree = encoder.serializeTree();
    std::string encodedText = encoder.encode();
    size_t treeSize = serializedTree.size();
    std::vector<uint8_t> treeSizeData(sizeof(size_t));
    for (size_t i = 0; i < sizeof(size_t); ++i)
        treeSizeData[i] = (treeSize >> (i * 8)) & 0xFF;
    std::vector<uint8_t> combinedData;
    combinedData.insert(combinedData.end(), treeSizeData.begin(), treeSizeData.end());
    combinedData.insert(combinedData.end(), serializedTree.begin(), serializedTree.end());
    combinedData.insert(combinedData.end(), encodedText.begin(), encodedText.end());
    socket.send_to(asio::buffer(combinedData), server_endpoint);
}
