#include"../includes/Core/Core.hpp"


extern "C" void setup(Entity *entity)
{
    entity->yourVariables["clock"] = 0;
    entity->yourVariables["direction"] = 'L'; // Start moving down
}

extern "C" void loop(Entity *entity, std::vector<std::unique_ptr<Entity>> *entities)
{

}
