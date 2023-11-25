/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Render
*/

#include "Position.hpp"

#ifndef RENDER_HPP_
#define RENDER_HPP_

class Render : public AComponents{
    public:
        Render(sf:: IntRect rect, std::string path) {
            text.loadFromFile(path);
            rect = rect;
            spr.setTexture(text);
            spr.setTextureRect(rect);
            spr.setScale(1.5, 1.5);
            this->path = path;
            // spr.setScale(sf::Vector2f(1.5, 1.5));
        };
        Render(sf:: IntRect rect, std::string path, std::string sound) {
            text.loadFromFile(path);
            rect = rect;
            spr.setTexture(text);
            spr.setTextureRect(rect);
            spr.setScale(1.5, 1.5);
            this->path = path;
            soundBuffer.loadFromFile(sound);
            this->sound.setBuffer(soundBuffer);
            // spr.setScale(sf::Vector2f(1.5, 1.5));
        };
        ~Render(){};

        Render& operator=(const Render &other) {
            if (this != &other) {
                this->spr = other.spr;
                this->text.loadFromFile(other.path);
                this->rect = other.rect;
                this->color = other.color;
                this->path = other.path;
            }
            AComponents::operator=(other);
            IComponents::operator=(other);
            return *this;
        }

        // Set the rendering rectangle (texture coordinates) for the sprite
        void setRect(sf::IntRect newRect) {
            rect = newRect;
            spr.setTextureRect(rect);
        }

        // Set the path to the texture file
        void setPath(const std::string& newPath) {
            path = newPath;
            if (!text.loadFromFile(path)) {
                // Handle loading error here.
            }
            // Set the texture for the sprite using the loaded texture
            spr.setTexture(text);
        }

        sf::Sound *getSound() {
            return &sound;
        }

        sf::IntRect getRect() {
            return rect;
        }

        std::string getPath() {
            return path;
        }

        sf::Sprite spr;

    protected:
    private:
        //A RAJOUTER SFTEXT ETC
        sf::Texture text;
        sf::IntRect rect;
        std::string color;
        std::string path;
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;

        // Hitbox hitbox;
};

#endif /* !RENDER_HPP_ */
