#include<cmath>
#include"../includes/Core/Core.hpp"


extern "C" void setup(Entity *entity)
{
    entity->yourVariables["clock"] = 0;
    entity->yourVariables["direction"] = 'D'; // Start moving down
}

extern "C" void loop(Entity *entity, std::vector<std::unique_ptr<Entity>> *entities) {
    
    if (entity->getTimer()->checkTimer(0.0001)) {
        int clock = entity->yourVariables["clock"];
        entity->yourVariables["clock"] = clock + 1;
        if (clock == 1) {
            entity->yourVariables["initY"] = entity->getPos()->y;
            return;
        }

        std::size_t amplitude = 200;
        double frequency = 0.002; // Ajustez la fréquence pour obtenir une trajectoire complète.

        if ((entity->yourVariables["direction"]) == 'D') {
            if (entity->getPos()->y < (entity->yourVariables["initY"]) + amplitude) {
                entity->setDirection('D');
                entity->moveEntity();
                double time = clock * 0.1; // Utiliser clock comme une variable de temps
                double xOffset = amplitude * sin(frequency * time); // Modifier la position x en fonction de la sinusoïde courbée
                entity->getPos()->x += xOffset;
            } else {
                entity->yourVariables["direction"] = 'U';
            }
        } else if ((entity->yourVariables["direction"]) == 'U') {
            if (entity->getPos()->y > (entity->yourVariables["initY"]) - amplitude) {
                entity->setDirection('U');
                entity->moveEntity();
                double time = clock * 0.1; // Utiliser clock comme une variable de temps
                double xOffset = amplitude * sin(frequency * time); // Modifier la position x en fonction de la sinusoïde courbée
                entity->getPos()->x += xOffset;
            } else {
                entity->yourVariables["direction"] = 'D';
            }
        }
        entity->setDirection('R');
        entity->moveEntity(); // Pour déplacer l'entité vers la droite, en plus de la trajectoire sinusoïdale.
        entity->send = true;
        entity->getTimer()->ResetTimer();
    }
}
