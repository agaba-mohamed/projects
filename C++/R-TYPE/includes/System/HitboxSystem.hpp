/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** HitboxSystem
*/

#pragma once

#ifndef HITBOXSYSTEM_HPP_
#define HITBOXSYSTEM_HPP_

#include "../../src/Entity/Entity.cpp"

class HitboxSystem {
public:
    HitboxSystem() {}
    ~HitboxSystem() {}

    std::string hitboxCollision(std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity1 : entities) {
            auto hitbox1 = dynamic_cast<Hitbox*>(entity1->getComponent<Hitbox>());
            if (!hitbox1->isActive)
                continue;
            for (auto& entity2 : entities) {
                if (entity1->getId() == entity2->getId())
                    continue;
                auto hitbox2 = dynamic_cast<Hitbox*>(entity2->getComponent<Hitbox>());
                if (!hitbox2->isActive)
                    continue;
                if (hitbox1->intersect(*hitbox2)) {
                        if ((entity1->getType() == "player" && entity2->getType().find("enemy") != std::string::npos) || (entity1->getType() == "player" && entity2->getType() == "obstacle") || (entity1->getType().find("bullet") != std::string::npos && entity2->getType().find("enemy") != std::string::npos) || (entity2->getType().find("bullet") != std::string::npos && entity1->getType().find("enemy") != std::string::npos)) {
                            entity1.get()->setHealth(0);
                            entity2.get()->setHealth(0);
                            hitbox1->isActive = false;
                            hitbox2->isActive = false;
                            std::string message = std::to_string(entity1->getId()) + " " + std::to_string(entity2->getId()) + " " + "collision";
                            return message;
                        }
                }
            }
        }
        return "";
    }

std::vector<std::string> handleCollision(std::vector<std::unique_ptr<Entity>>& entities, const std::string& data) {
    std::vector<std::string> newEntityInfo;
    if (!data.empty()) {
        std::istringstream iss(data);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        
        if (tokens.size() == 3 && tokens[2] == "collision") {
            try {
                int id1 = std::stoi(tokens[0]);
                int id2 = std::stoi(tokens[1]);
                
                for (auto& entity : entities) {
                    if (entity->getId() == id1) {
                        newEntityInfo.push_back(std::to_string(entity->getPos()->x));
                        newEntityInfo.push_back(std::to_string(entity->getPos()->y));
                        newEntityInfo.push_back("explosion");
                        entity->setHealth(0);
                        auto hitbox1 = dynamic_cast<Hitbox*>(entity->getComponent<Hitbox>());
                        if (hitbox1) {
                            hitbox1->isActive = false;
                        }
                    }
                    if (entity->getId() == id2) {
                        entity->setHealth(0);
                        auto hitbox2 = dynamic_cast<Hitbox*>(entity->getComponent<Hitbox>());
                        if (hitbox2) {
                            hitbox2->isActive = false;
                        }
                    }
                }
                return newEntityInfo;
            } catch (std::invalid_argument& e) {
                std::cout << "Invalid Integer" << std::endl;
            }
        }
    }
    return newEntityInfo;
}

};


#endif /* !HITBOXSYSTEM_HPP_ */
