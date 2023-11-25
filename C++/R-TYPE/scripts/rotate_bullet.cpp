#include"../includes/Core/Core.hpp"

extern "C" void setup(Entity *entity)
{
    entity->yourVariables["clock"] = 0;
    entity->yourVariables["direction"] = 'D'; // Start moving down
    entity->yourVariables["turns"] = 0; // Initialize the variable for counting the number of turns
    entity->yourVariables["initX"] = entity->getPos()->x; // Initialize the starting x position
}

extern "C" void loop(Entity *entity, std::vector<std::unique_ptr<Entity>> *entities)
{
    if (entity->getTimer()->checkTimer(0.0001)) {
        int clock = entity->yourVariables["clock"];

        entity->yourVariables["clock"] = clock + 1;
        if (clock == 1) {
            entity->yourVariables["initY"] = entity->getPos()->y;
            return;
        }
        std::size_t amplitude = 200;
        if ((entity->yourVariables["direction"]) == 'D') {
            if (entity->getPos()->y < (entity->yourVariables["initY"]) + amplitude) {
                entity->setDirection('D');
                entity->moveEntity();
            } else {
                entity->yourVariables["direction"] = 'R'; // Change direction to move to the right
            }
        }
        else if ((entity->yourVariables["direction"]) == 'R') {
            if (entity->getPos()->x < (entity->yourVariables["initX"]) + amplitude) {
                entity->setDirection('R');
                entity->moveEntity();
            } else {
                entity->yourVariables["direction"] = 'U'; // Change direction to move up
            }
        }
        else if ((entity->yourVariables["direction"]) == 'U') {
            if (entity->getPos()->y > (entity->yourVariables["initY"])) {
                entity->setDirection('U');
                entity->moveEntity();
            } else {
                entity->yourVariables["direction"] = 'L'; // Change direction to move to the left
            }
        }
        else if ((entity->yourVariables["direction"]) == 'L') {
            if (entity->getPos()->x > (entity->yourVariables["initX"])) {
                entity->setDirection('L');
                entity->moveEntity();
            } else {
                entity->yourVariables["direction"] = 'D'; // Change direction to move down

                // Increment the number of turns and update the starting x position
                entity->yourVariables["turns"] = entity->yourVariables["turns"] + 1;
                entity->yourVariables["initX"] = entity->yourVariables["initX"] + amplitude;
            }
        }
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }
}
