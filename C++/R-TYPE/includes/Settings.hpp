/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: fedora]
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <iostream>
#include <memory>
#include <array>
#include <queue>
#include <asio.hpp>
#include <string>
#include <thread>
#include <asio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Settings {
    public:
        Settings();
        ~Settings();

        void settingsGestion(sf::RenderWindow &win);
        void drawSettings(sf::RenderWindow &win);

        bool isSettingsOpen;
        sf::Font font;

        sf::Texture settingsIconTexture;
        sf::Sprite  settingsIconSprite;
        sf::RectangleShape backgroundRect;
        sf::Text settingsTitileText;
        sf::Text logoutText;

    protected:
    private:
};

#endif /* !SETTINGS_HPP_ */
