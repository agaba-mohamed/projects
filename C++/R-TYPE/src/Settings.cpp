/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: fedora]
** File description:
** Settings
*/

#include "../includes/Settings.hpp"

Settings::Settings()
{
    isSettingsOpen = false;
    font.loadFromFile("../assets/Crang.ttf");

    sf::Color fillColor(0x241C1CFF);
    sf::Color outlineColor(0x7D7D7DFF);

    settingsTitileText.setFont(font);
    settingsTitileText.setCharacterSize(48);
    settingsTitileText.setFillColor(fillColor);
    settingsTitileText.setOutlineColor(outlineColor);
    settingsTitileText.setOutlineThickness(2.0f);
    settingsTitileText.setPosition(780.f, 250.f);
    settingsTitileText.setString("Parametres");

    logoutText.setFont(font);
    logoutText.setCharacterSize(32);
    logoutText.setFillColor(fillColor);
    logoutText.setOutlineColor(outlineColor);
    logoutText.setOutlineThickness(2.0f);
    logoutText.setPosition(820.f, 860.f);
    logoutText.setString("Se deconnecter");

    settingsIconTexture.loadFromFile("../assets/settings_icon.png");
    settingsIconSprite.setTexture(settingsIconTexture);
    settingsIconSprite.setPosition(50.f, 60.f);

    backgroundRect.setSize(sf::Vector2f(1680, 700));
    backgroundRect.setPosition(120.f, 220.f);
    backgroundRect.setFillColor(fillColor);
    backgroundRect.setOutlineColor(outlineColor);
    backgroundRect.setOutlineThickness(2);
}

Settings::~Settings()
{
}

void Settings::settingsGestion(sf::RenderWindow &win)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(win);

    if (isSettingsOpen) {
        sf::FloatRect logoutBounds = logoutText.getGlobalBounds();
        if (logoutBounds.contains(sf::Vector2f(mousePosition))) {
            logoutText.setOutlineColor(sf::Color::White);
        } else {
            logoutText.setOutlineColor(sf::Color(0x7D7D7DFF));
        }
    } else {
        sf::FloatRect settingsBounds = settingsIconSprite.getGlobalBounds();
        if (settingsBounds.contains(sf::Vector2f(mousePosition))) {
            settingsIconSprite.setColor(sf::Color::White);
        } else {
            settingsIconSprite.setColor(sf::Color(0x7D7D7DFF));
        }
    }
}

void Settings::drawSettings(sf::RenderWindow &win)
{
    if (isSettingsOpen) {
        win.draw(settingsIconSprite);
        win.draw(backgroundRect);
        win.draw(settingsTitileText);
        win.draw(logoutText);
    } else {
        win.draw(settingsIconSprite);
    }
}
