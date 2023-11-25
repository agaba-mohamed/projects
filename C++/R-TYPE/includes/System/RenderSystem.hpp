/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#pragma once

#include "HitboxSystem.hpp"

class RenderSystem {
public:
    RenderSystem() {}
    ~RenderSystem() {}
    void render(std::vector<std::unique_ptr<Entity>> &entities, sf::RenderWindow &win) {
        _time = _clock.getElapsedTime();
        _second = _time.asSeconds();
        for (auto& entity : entities) {
            if (entity->getType() == "explosion") {
                if (_second > 2) {
                    sf::IntRect rect = entity->getRender()->getRect();
                    if (rect.left < 196) {
                        rect.left += 22;
                        entity->setRender(rect, entity->getRender()->getPath());
                        if (rect.left >= 196) {
                            entity->setHealth(0);
                        }
                    }
                    _clock.restart();
                }
            }
            if (entity->getHealth() > 0) {
                entity->display(win);
            }
        }
        win.display();
    }
protected:
private:
        sf::Time    _time;
        sf::Clock   _clock;
        float       _second;
};
