// chase_bullet.cpp

#include <cstdlib> // Pour l'utilisation de rand() et srand()
#include <ctime> 
#include"../includes/Core/Core.hpp"
#include <cmath>
extern "C" void setup(Entity *entity)
{
}

extern "C" void loop(Entity *entity, std::vector<std::unique_ptr<Entity>> *entities)
{
    if (entity->getTimer()->checkTimer(0.0001)) {
        int id = -1;
        float minDistance = std::numeric_limits<float>::max();
        // sf::Vector2f bulletPos = entity->getPos();
        for (auto &a : *entities) {
            if (a->getType().find("basic_enemy") != std::string::npos || a->getType().find("obstacle") != std::string::npos) {
                // sf::Vector2f aPos = a->getPos();
                float distance = std::sqrt(std::pow(entity->getPos()->x - a->getPos()->x, 2) + std::pow(entity->getPos()->y - a->getPos()->y, 2));
                if (distance < minDistance) {
                    minDistance = distance;
                    id = a->getId();
                }
            }
        }
        if(id != -1) {
            if (entities->at(id)->getPos()->y > entity->getPos()->y) {
                entity->setDirection('D');
                entity->moveEntity();
            } if (entities->at(id)->getPos()->y < entity->getPos()->y) {
                entity->setDirection('U');
                entity->moveEntity();
            }
        }
        entity->setDirection('R');
        entity->moveEntity();
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }
}
