#include <cstdlib> // Pour l'utilisation de rand() et srand()
#include <ctime> 
#include"../includes/Core/Core.hpp"



extern "C" void setup(Entity *entity)
{
    entity->yourVariables["clock"] = 0;
    entity->yourVariables["direction"] = 'D'; // Start moving down
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

        std::srand(std::time(0)); // use current time as seed for random generator
        std::size_t amplitude = 200;
        if ((entity->yourVariables["direction"]) == 'D') {
            if (entity->getPos()->y < (entity->yourVariables["initY"]) + amplitude) {
                entity->setDirection('D');
                entity->moveEntity(); // Mouvement vers le bas
            } else {
                // Génération d'une direction aléatoire 'U' ou 'D'
                if (std::rand() % 2 == 0) {
                    entity->yourVariables["direction"] = 'U'; // Changement de direction vers le haut
                } else {
                    entity->yourVariables["direction"] = 'D'; // Changement de direction vers le bas
                }
            }
        } else if ((entity->yourVariables["direction"]) == 'U') {
            if (entity->getPos()->y > (entity->yourVariables["initY"]) - amplitude) {
                entity->setDirection('U');
                entity->moveEntity(); // Mouvement vers le haut
            } else {
                // Génération d'une direction aléatoire 'U' ou 'D'
                if (std::rand() % 2 == 0) {
                    entity->yourVariables["direction"] = 'U'; // Changement de direction vers le haut
                } else {
                    entity->yourVariables["direction"] = 'D'; // Changement de direction vers le bas
                }
            }
        }
        entity->setDirection('R');
        entity->moveEntity();
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }

}
