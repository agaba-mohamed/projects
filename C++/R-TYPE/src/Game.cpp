
#include "../includes/Game.hpp"

Game::Game()
{
    win.create(sf::VideoMode(970,622),"Test");
    win.setFramerateLimit(60);
    std::vector<std::string> files = listFilesInFolder("../entities");
    for (int i = 0; i != files.size();i++) {
        EntityType EntityType("../entities/" + files.at(i));
        entities_type.push_back(EntityType);
    }
}

Game::Game(bool display)
{
    this->is_display = display;
    if(display) {
        win.create(sf::VideoMode(970,622),"Test");
        win.setFramerateLimit(60);
    }
    std::vector<std::string> files = listFilesInFolder("../entities");
    for (int i = 0; i != files.size();i++) {
        EntityType entityType("../entities/" + files.at(i));
        entities_type.push_back(entityType);
    }
}

void Game::render()
{
    for (int  i = 0;i != entities.size();i++) {
        if(!entities.at(i).text.empty() && entities.at(i).render) {
            sf::Texture texture;
            sf::Sprite sprite;
            sf::IntRect rect;
            rect.left = entities.at(i).rect.left;
            rect.top = entities.at(i).rect.top;
            rect.height = entities.at(i).rect.bottom;
            rect.width = entities.at(i).rect.right;
            texture.loadFromFile(entities.at(i).text);
            sprite.setTexture(texture);
            sprite.setPosition(entities.at(i).pos.x,entities.at(i).pos.y);
            sprite.setTextureRect(rect);
            sprite.setScale(entities.at(i).size.x,entities.at(i).size.y);
            win.draw(sprite);
        }
    }
    win.display();
}

void Game::inside()
{}

void Game::add(std::string type) {
    for (int i = 0;i != entities_type.size();i++) {
        if(type == entities_type.at(i).name) {
            EntityType entity;
            entity.script = entities_type.at(i).script;
            entity.health = entities_type.at(i).health;
            entity.hitbox = entities_type.at(i).hitbox;
            entity.name = entities_type.at(i).name;
            entity.pos = entities_type.at(i).pos;
            entity.rect = entities_type.at(i).rect;
            entity.size = entities_type.at(i).size;
            entity.text = entities_type.at(i).text;
            entity.render = entities_type.at(i).render;
            entity.weapon = entities_type.at(i).weapon;
            entities.push_back(entity);
        }
    }
}