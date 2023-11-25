/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: Ubuntu]
** File description:
** Server
*/

#include "../../includes/Server/Server.hpp"

std::string last_mess;

Server::Server(std::size_t port, std::size_t player_number, std::string map) : core(false)
{
    this->port = port;
    this->player_numbers = player_number;
    this->map = map;
    this->enemy_numbers = 100;
    server_thread = std::thread([this]() {
        for (;;)
        this->launchServer();
    });
}

void Server::launchServer()
{
    try {
        std::cout << "Launching server on port: " << port << std::endl;
        this->io_context = std::make_unique<asio::io_context>();
        socket = std::make_unique<asio::ip::udp::socket>(*io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
        socket->async_receive_from(asio::buffer(receive_buffer), sender_endpoint,
                                  std::bind(&Server::receive, this, std::placeholders::_1, std::placeholders::_2, std::ref(*socket)));
        client_thread = std::thread([this]() {
            for (;;)
                handleClients(sender_endpoint);
        });
        collision_thread = std::thread([this]() {
            for (;;)
                handleCollision();
        });
        movement_thread = std::thread([this]() {
            for (;;)
                handleMovement();
        });
        // entity_thread = std::thread([this]() {
        //     for (;;)
        //         handleEntity();
        // });
        std::cout << "Sever Launched " << std::endl;
        this->io_context->run();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

Server::~Server()
{
    client_thread.join();
    collision_thread.join();
    movement_thread.join();
    entity_thread.join();
}

void Server::handleCollision()
{
    if (core.entities.size() > enemy_numbers + player_numbers - 1) {
        dataToSend = core.handlePackage(data, 1000);
        if (dataToSend != "")
            for (std::size_t i = 1; i < players_info.size(); i++)
                send(dataToSend, players_info.at(i));
        dataToSend = "";
        dataToSend = core.hitbox.hitboxCollision(core.entities);
        if (dataToSend != "")
            for (std::size_t i = 1; i < players_info.size(); i++)
                send(dataToSend, players_info.at(i));
        dataToSend = "";
    }
}

void Server::handleEntity() {
    if (core.entities.size() > enemy_numbers + player_numbers - 1) {
        for (auto it = core.entities.begin(); it != core.entities.end();) {
            auto& entity = *it;

            if (entity->getType() == "basic_enemy" && entity->getPos()->x < -200) {
                core.entities.erase(it);
                enemy_numbers -= 1;
            }
            else if (entity->getType() == "bullet" && entity->getPos()->x > 1920) {
                it = core.entities.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void Server::handleMovement()
{
    if (core.entities.size() > enemy_numbers + player_numbers - 1) {
        for (auto &entity : core.entities)
            if (entity->getType() != "player") {
                entity->getTimer()->startTimer();
            }

        for (auto &entity : core.entities) {
            if (!entity->file.empty()) {
                typedef void (*ProcessDataFunc)(Entity*,std::vector<std::unique_ptr<Entity>>*);
                #ifdef _WIN32
                    std::wstring script(entity->file.begin(), entity->file.end());
                    HMODULE libHandle = OPENLIB(script.c_str());
                    ProcessDataFunc loop = (ProcessDataFunc)GetProcAddress(libHandle, "loop");
                #elif __linux__
                    std::string script =  entity->file;
                    void* libHandle = OPENLIB(script.c_str());
                    ProcessDataFunc loop = (ProcessDataFunc)LIBFUNC(libHandle, "loop");
                #endif
                if (entity->getType() != "player") {
                    if (loop) {
                        Entity* entityRawPtr = entity.get();
                        loop(entityRawPtr, &core.entities);
                    }
                }
            }
        }
    }  
}

void Server::handleClients(asio::ip::udp::endpoint clientEndpoint)
{
    if (this->players_info.size() > 1) {
        for (std::size_t i = 1; i < players_info.size(); i++) {
            for (auto &entity : core.entities) {
                if (entity->getType() != "player" && entity->send && entity->getPos()->x < 1920 && entity->getPos()->x >= (-200) && entity->getHealth() > 0) {
                    send("Id: " +  std::to_string(entity->getId()) + ": " +  "x: " + std::to_string(entity->getPos()->x) + " y: " + std::to_string(entity->getPos()->y) + " type: " + entity->getType() , players_info.at(i));
                    entity->send = false;
                }

            }
        }
    }
    for (std::size_t i = 0; i < players_info.size(); i++) {
        if (players_info.at(i).address() == clientEndpoint.address())
            return;
    }
    this->players_info.push_back(clientEndpoint);
    if (this->players_info.size() > 1) {
        for (std::size_t i = 1; i < players_info.size(); i++)
            send("Id: " + std::to_string(core.entities_number) + "x:" + std::to_string(500) + " y:" + std::to_string(250) + " type: player" , players_info.at(i));
        core.createEntity(this->core.entities_number, 500, 250, "player");
    }
    if (this->core.entities_number == player_numbers) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::ifstream inputFile("../maps/" + map);

        if (!inputFile.is_open())
            std::cerr << "Error: Unable to open the file." << std::endl;

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line))
            lines.push_back(line);

        inputFile.close();
        std::size_t numbers = 0;
        Game temp_game(false);
        for (int i = 0; i < lines.size(); ++i) {
                for (int j = 0; j < lines[i].size(); ++j) {
                    for (int k = 0;k != temp_game.entities_type.size();k++)
                    if (lines[i][j] == temp_game.entities_type.at(k).fileDesc.front()) {
                        // send("Id: " + std::to_string(core.entities_number) + "x:" + std::to_string(j * 250) + " y:" + std::to_string(i * 115) + " type: " + temp_game.entities_type.at(k).name, clientEndpoint);
                        core.createEntity(core.entities_number, j * 250, i * 115, temp_game.entities_type.at(k).name);
                        numbers += 1;
                    }
                }
        }
        this->enemy_numbers = numbers;
    }

}

void Server::send(std::string message, asio::ip::udp::endpoint clientEndpoint)
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
    socket->send_to(asio::buffer(combinedData), clientEndpoint);
}


struct EntityInfo {
    int id;
    int x;
    int y;
    std::string type;
};

EntityInfo parseReceived(const std::string& input) {
    EntityInfo info;

    std::istringstream iss(input);
    info.id = -1;
    std::string token;
    while (iss >> token) {
        if (token == "Id:") {
            iss >> info.id;
        } else if (token == "x:") {
            iss >> info.x;
        } else if (token == "y:") {
            iss >> info.y;
        } else if (token == "type:") {
            iss >> info.type;
        }
    }

    return info;
}

void Server::receive(const asio::error_code& error, std::size_t bytes_received, asio::ip::udp::socket& socket)
{
    if (!error && bytes_received > 0) {
        HuffmanDecoder decoder;
        size_t extractedTreeSize = 0;
        for (size_t i = 0; i < sizeof(size_t); ++i) 
            extractedTreeSize |= static_cast<size_t>(receive_buffer[i]) << (i * 8);
        std::vector<uint8_t> serializedTreePart(receive_buffer.begin() + sizeof(size_t), receive_buffer.begin() + sizeof(size_t) + extractedTreeSize);
        std::string encodedTextPart(receive_buffer.begin() + sizeof(size_t) + extractedTreeSize, receive_buffer.begin() + bytes_received);
        decoder.deserializeTree(serializedTreePart);
        std::string decodedText = decoder.decode(encodedTextPart);
        std::string decrypted(decodedText);
        std::istringstream iss(decrypted);
        if(parseReceived(decrypted).id != -1) {
            if(decrypted.find("shoot") != std::string::npos) {
                core.createEntity(core.entities.size(),core.entities.at(parseReceived(decrypted).id)->getPos()->x,core.entities.at(parseReceived(decrypted).id)->getPos()->y,core.entities.at(parseReceived(decrypted).id)->weapon);
            } else {
                core.entities.at(parseReceived(decrypted).id)->setPos(parseReceived(decrypted).x,parseReceived(decrypted).y,'N',10);
                core.entities.at(parseReceived(decrypted).id)->setHitbox(parseReceived(decrypted).x,parseReceived(decrypted).y);
            }
        }
        for (std::size_t i = 1; i < players_info.size(); i++) 
            send(decodedText, players_info.at(i));
        socket.async_receive_from(asio::buffer(receive_buffer), sender_endpoint,
        std::bind(&Server::receive, this, std::placeholders::_1, std::placeholders::_2, std::ref(socket)));
    }
}
