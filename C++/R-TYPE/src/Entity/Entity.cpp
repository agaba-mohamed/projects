/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Entity
*/

#include "../../includes/Entity/Entity.hpp"
#include "../Game.cpp"

Entity::Entity(std::size_t id ,float x,float y, std::string type)
{
    this->id = id;
    this->type = type;
    sf::IntRect rect;
    std::string sprite;
    std::unique_ptr<IComponents> render = nullptr;
    std::unique_ptr<IComponents> hitbox = nullptr;
    std::unique_ptr<IComponents> position = nullptr;
    std::unique_ptr<IComponents> timer = nullptr;
    std::unique_ptr<IComponents> health = std::make_unique<Health>(100);
    Game temp_game(false);
    temp_game.add(type);
    position = std::make_unique<Position>(x, y, temp_game.entities.back().pos.direction, 0.02);
    rect.left = temp_game.entities.back().rect.left;
    rect.top = temp_game.entities.back().rect.top;
    rect.height = temp_game.entities.back().rect.bottom;
    rect.width = temp_game.entities.back().rect.right;
    timer = std::make_unique<Timer>();
    if(temp_game.entities.back().render) {
        if(this->type != "explosion")
            sprite.assign("../assets/sounds/shoot1.wav");
        else
            sprite.assign("../assets/sounds/destruction.wav");
    }
    render = std::make_unique<Render>(rect,temp_game.entities.back().text, sprite);
    if(temp_game.entities.back().hitbox) {
        hitbox = std::make_unique<Hitbox>(x, y, rect.height, rect.width);
        components.push_back(std::move(hitbox));
    }
    components.push_back(std::move(timer));
    components.push_back(std::move(position));
    components.push_back(std::move(health));
    components.push_back(std::move(render));
    if (type == "bullet" || type == "explosion")
        getRender()->getSound()->play();
    file = temp_game.entities.back().script;
    if (!file.empty()) {
    typedef void (*ProcessDataFunc)(Entity*);
        #ifdef __linux__
            void* libHandle = OPENLIB(file.c_str());
            ProcessDataFunc setup = (ProcessDataFunc)LIBFUNC(libHandle, "setup");
        #elif _WIN32
            std::wstring script(file.begin(), file.end());
            HMODULE libHandle = OPENLIB(script.c_str());
            ProcessDataFunc setup = (ProcessDataFunc)GetProcAddress(libHandle, "setup");

        #endif
        if (setup)
        setup(this);
    }
}

Entity::Entity(std::size_t id ,float x,float y, std::string type,int player)
{
    Game temp_game(false);
    temp_game.add(type);
    this->id = id;
    this->type = type;
    sf::IntRect rect;
    std::unique_ptr<IComponents> render = nullptr;
    std::unique_ptr<IComponents> hitbox = nullptr;
    std::unique_ptr<IComponents> position = nullptr;
    std::unique_ptr<IComponents> health = std::make_unique<Health>(100);
    position = std::make_unique<Position>(x, y, 'N', 10);
    rect.left = 0;
    rect.height = 17.2;
    rect.top = (player) * rect.height;
    rect.width = 33;
    hitbox = std::make_unique<Hitbox>(x, y, rect.height, rect.width);
    render = std::make_unique<Render>(rect, "../assets/sprites/r-typesheet42.gif");
    components.push_back(std::move(position));
    components.push_back(std::move(health));
    components.push_back(std::move(render));
    components.push_back(std::move(hitbox));
    this->weapon = temp_game.entities.back().weapon;
    file = temp_game.entities.back().script;
}


std::string Entity::handleEvents(sf::RenderWindow &win, sf::Event &windowEvent)
{
    std::string return_message = "Id: " + std::to_string(this->getId()) + ": ";
    while (win.pollEvent(windowEvent)) {
        if (windowEvent.type == sf::Event::Closed)
            exit(0);
        if (windowEvent.type == sf::Event::KeyReleased && windowEvent.key.code == sf::Keyboard::Space && getHealth() > 0) {
            return_message += "shoot";
            return return_message;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPos()->x < 1920) {
        std::unique_ptr<Position> pos = getPos(); 
        setPos(pos->x, pos->y, 'R', pos->speed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPos()->x > 0) {
        std::unique_ptr<Position> pos = getPos(); 
        setPos(pos->x, pos->y, 'L', pos->speed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && getPos()->y > 40) {
        std::unique_ptr<Position> pos = getPos(); 
        setPos(pos->x, pos->y, 'U', pos->speed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && getPos()->y < 960) {
        std::unique_ptr<Position> pos = getPos(); 
        setPos(pos->x, pos->y, 'D', pos->speed);
    } else {
        return "";
    }
    moveEntity();
    return_message += "x: " + std::to_string(getPos()->x) + " y: " + std::to_string(getPos()->y) + " type: player";
    return(return_message);
}


void Entity::display(sf::RenderWindow &win)
{
    setRenderPos();
    win.draw(getRender()->spr);
}

void Entity::moveEntity() {
    std::unique_ptr<Position> pos = getPos();
    if (pos->direction == 'L') pos->x -= pos->speed;
    if (pos->direction == 'R') pos->x += pos->speed;
    if (pos->direction == 'U') pos->y -= pos->speed;
    if (pos->direction == 'D') pos->y += pos->speed;

    setPos(pos->x, pos->y, pos->direction, pos->speed);
    setHitbox(pos->x, pos->y);
}

void Entity::predictEnemyMovement() {
    std::unique_ptr<Position> pos = getPos();
    pos->x -= 5;
    setPos(pos->x, pos->y, pos->direction, pos->speed);
    setHitbox(pos->x, pos->y);

}

void Entity::predictBulletMovement() {
    std::unique_ptr<Position> pos = getPos();
    pos->x += 5;
    setPos(pos->x, pos->y, pos->direction, pos->speed);
    setHitbox(pos->x, pos->y);

}

void Entity::setPos(float x, float y, char direction, float speed)
{
    Position* posComponent = getComponent<Position>();

    if (posComponent) {
        posComponent->x = x;
        posComponent->y = y;
        posComponent->direction = direction;
        posComponent->speed = speed;
    }
}

void Entity::setDirection(char direction)
{
    Position* posComponent = getComponent<Position>();

    if (posComponent) {
        posComponent->direction = direction;
    }
}


std::unique_ptr<Position> Entity::getPos()
{
    Position* posComponent = getComponent<Position>();

    if (posComponent)
        return std::make_unique<Position>(*posComponent);

    return nullptr;
}

void Entity::setRender(sf::IntRect rect, std::string path)
{
    Render* renderComponent = getComponent<Render>();

    if (renderComponent) {
        renderComponent->setRect(rect);
        renderComponent->setPath(path);
    }
}

Render* Entity::getRender()
{
    Render* renderComponent = getComponent<Render>();
    if (renderComponent)
        return renderComponent;
    return nullptr;
}


void Entity::setRenderPos()
{
    Render* renderComponent = getComponent<Render>();
    if (renderComponent)
        renderComponent->spr.setPosition((getPos()->x),getPos()->y);
}


void Entity::setHealth(std::size_t newHealth)
{
    Health* healthComponent = getComponent<Health>();

    if (healthComponent)
        healthComponent->setValue(newHealth);
}

std::size_t Entity::getHealth()
{
    Health* healthComponent = getComponent<Health>();

    if (healthComponent)
        return healthComponent->getValue();

    return 100;
}

void Entity::setHitbox(std::size_t left, std::size_t top)
{
    Hitbox* hitboxComponent = getComponent<Hitbox>();

    if (hitboxComponent) {
        hitboxComponent->pos.x = left;
        hitboxComponent->pos.y = top;
    }
    else {
        std::unique_ptr<Hitbox> newHitbox = std::make_unique<Hitbox>(left, top, hitboxComponent->height, hitboxComponent->width);
        components.push_back(std::move(newHitbox));
    }
}

Timer* Entity::getTimer()
{
    Timer* timerComponent = getComponent<Timer>();
    if (timerComponent)
        return timerComponent;
    else
        return nullptr;
}



void Entity::setType(std::string type)
{
    this->type = type;
}

std::string Entity::getType() {
    return type;
}

void Entity::setId(std::size_t Id)
{
    this->id = Id;
}

std::size_t Entity::getId()
{
    return id;
}

Entity::~Entity() {

}
