/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#pragma once

#include "../../src/Menu.cpp"
// #include"../System/SpawningSystem.hpp"
// #include"../System/RenderSystem.hpp"
#include"../System/HitboxSystem.hpp"
#include"../../src/Settings.cpp"

class Core {
    public:
        Core(bool screen);
        ~Core();
        void displayAll();//replace
        void createEntity(std::size_t id, float x, float y, std::string type);//modify
        std::string handlePackage(std::string data, std::size_t index);//modify if possible

        std::vector<std::unique_ptr<Entity>> entities;
        RenderSystem render;
        HitboxSystem hitbox;
        sf::Event windowEvent;
        sf::RenderWindow win;
        sf::VideoMode desktopMode;
        sf::Sprite backgroundSprite1;
        sf::Sprite backgroundSprite2;
        sf::Texture _middlegroundTexture;
        sf::Sprite  _middlegroundSprite;
        sf::Texture backgroundText;
        std::size_t entities_number = 0;
        std::size_t roomCreating = 0;
        int player_number = 0;
        bool screen;

        int actualScreen;
        bool isSettingsOpen;

        Menu menu;
        Settings settings;

        sf::Sound backgroundMusic;
        sf::SoundBuffer backgroundMusicBuffer;

        /*Fonctions event clique menu page 1*/
        void eventGestion(sf::Vector2f mousePosition, std::string &message);
        void closePopUp(sf::Vector2f mousePosition, std::string &message);
        void openSettings(sf::Vector2f mousePosition);
        void logout(sf::Vector2f mousePosition);
        void createGameButton(sf::Vector2f mousePosition, std::string &message);
        void inputGameName(sf::Vector2f mousePosition);
        void selectLevel(sf::Vector2f mousePosition);
        void selectNbPlayers(sf::Vector2f mousePosition);
        void changeMap(sf::Vector2f mousePosition);
        std::string createRoom(sf::Vector2f mousePosition);
        std::string launchGame(sf::Vector2f mousePosition);

    protected:
    private:
};

#endif /* !CORE_HPP_ */