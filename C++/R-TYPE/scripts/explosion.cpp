#include"../includes/Core/Core.hpp"

extern "C" void setup(Entity *entity)
{
}

extern "C" void loop(Entity *entity,std::vector<std::unique_ptr<Entity>> *entities)
{
    if (entity->getTimer()->checkTimer(0.1)) {
        sf::IntRect rect = entity->getRender()->getRect();
        if (rect.left < 32.6) {
            rect.left += 32.6;
            if (rect.left >= 196) entity->setHealth(0);
        }
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }
}