#include"../includes/Core/Core.hpp"

extern "C" void setup(Entity *entity)
{
}

extern "C" void loop(Entity *entity,std::vector<std::unique_ptr<Entity>> *entities)
{
    if (entity->getTimer()->checkTimer(0.0001)) {
        entity->moveEntity();
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }
}