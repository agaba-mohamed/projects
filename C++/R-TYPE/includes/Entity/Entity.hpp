/*
** EPITECH PROJECT, 2023
** aaaa
** File description:
** aaaa
*/

#include "../Components/Hitbox.hpp"
#include<any>

class Entity {
    public:

        Entity(std::size_t id ,float x,float y, std::string type);
        Entity(std::size_t id ,float x,float y, std::string type,int);
        ~Entity();

        std::string handleEvents(sf::RenderWindow &win, sf::Event &windowEvent);

        void display(sf::RenderWindow &win);

        void moveEntity();

        void predictEnemyMovement();

        void predictBulletMovement();
        
        void setPos(float x, float y, char direction = 0, float speed = 0);

        void setDirection(char direction);

        std::unique_ptr<Position> getPos();

        void setRender(sf::IntRect rect, std::string path);

        Render* getRender();

        void setRenderPos();

        void setHealth(std::size_t newHealth);

        std::size_t getHealth();

        void setHitbox(std::size_t left, std::size_t top);

        Timer* getTimer();

        void setType(std::string type);

        std::string getType();

        void setId(std::size_t Id);

        std::size_t getId();

        template <typename T>
        T* getComponent() {
            for (std::unique_ptr<IComponents>& component : components) {
                if (auto componentOfType = dynamic_cast<T*>(component.get())) {
                    return componentOfType;
                }
            }
            return nullptr;
        }

        std::vector<std::unique_ptr<IComponents>> components;
        std::size_t id;
        std::string file;//add composant
        std::string weapon;//add composant
        std::string received = "";
        std::string fileDesc; //add composant
        std::map<std::string, int> yourVariables;
        bool send = false;
        //vecteur de variables à ajouter
    protected:
    private:
        std::string type;
};
