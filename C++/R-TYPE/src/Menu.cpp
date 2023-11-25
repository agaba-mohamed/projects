/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Menu
*/

#include "../includes/Menu.hpp"

Menu::Menu()
{
    _clock.restart();
    _clock2.restart();
    _isSomethingWritePseudo = false;
    _isSomethingWriteIp = false;
    _isSomethingWritePort = false;
    _isTyping = false;
    _switchTyping = 0;
    _menuPage = 0;

    _isTypingPseudo = false;
    _isTypingIp = false;
    _isTypingPort = false;

    _infosLobbyTexture.loadFromFile("../assets/info.png");
    _infosLobbySprite.setTexture(_infosLobbyTexture);

    _font.loadFromFile("../assets/Crang.ttf");

    _inputText.setFont(_font);
    _inputText.setCharacterSize(32);
    _inputText.setFillColor(sf::Color(0x241C1CFF));
    _inputText.setOutlineColor(sf::Color(0x7D7D7DFF));
    _inputText.setOutlineThickness(2.0f);
    _inputText.setPosition(725.f, 400.f);
    _inputText.setString("Entrer votre pseudo");

    _inputIpText.setFont(_font);
    _inputIpText.setCharacterSize(32);
    _inputIpText.setFillColor(sf::Color(0x241C1CFF));
    _inputIpText.setOutlineColor(sf::Color(0x7D7D7DFF));
    _inputIpText.setOutlineThickness(2.0f);
    _inputIpText.setPosition(725.f, 500.f);
    _inputIpText.setString("IP");

    _inputPortText.setFont(_font);
    _inputPortText.setCharacterSize(32);
    _inputPortText.setFillColor(sf::Color(0x241C1CFF));
    _inputPortText.setOutlineColor(sf::Color(0x7D7D7DFF));
    _inputPortText.setOutlineThickness(2.0f);
    _inputPortText.setPosition(725.f, 600.f);
    _inputPortText.setString("Port");

    _playText.setFont(_font);
    _playText.setCharacterSize(48);
    _playText.setFillColor(sf::Color(0x241C1CFF));
    _playText.setOutlineColor(sf::Color(0x7D7D7DFF));
    _playText.setOutlineThickness(2.0f);
    _playText.setPosition(860.f, 700.f);
    _playText.setString("Jouer");

    _lobbiesText.setFont(_font);
    _lobbiesText.setCharacterSize(48);
    _lobbiesText.setFillColor(sf::Color(0x241C1CFF));
    _lobbiesText.setOutlineColor(sf::Color(0x7D7D7DFF));
    _lobbiesText.setOutlineThickness(2.0f);
    _lobbiesText.setPosition(855.f, 300.f);
    _lobbiesText.setString("Lobbies");

    _switchTyping = 0;
    _isSettingsOpen = false;

    initializeRect();
    _newGameText.setFont(_font);
    _newGameText.setCharacterSize(32);
    _newGameText.setFillColor(sf::Color(0x241C1CFF));
    _newGameText.setOutlineColor(sf::Color::White);
    _newGameText.setOutlineThickness(2.0f);
    _newGameText.setString("Nouvelle Partie");
    _newGameText.setOrigin(_newGameText.getLocalBounds().width / 2, _newGameText.getLocalBounds().height / 2);

    sf::Color fillColor(0x241C1CFF);
    sf::Color outlineColor(0x7D7D7DFF);

    _isNewGameOpen = false;

    _newGameRectBackground.setSize(sf::Vector2f(1680, 700));
    _newGameRectBackground.setPosition(120.f, 220.f);
    _newGameRectBackground.setFillColor(fillColor);
    _newGameRectBackground.setOutlineColor(outlineColor);
    _newGameRectBackground.setOutlineThickness(2);

    _startNewGame.setFont(_font);
    _startNewGame.setCharacterSize(32);
    _startNewGame.setFillColor(fillColor);
    _startNewGame.setOutlineColor(outlineColor);
    _startNewGame.setOutlineThickness(2.0f);
    _startNewGame.setString("Commencer !");
    sf::FloatRect startNewGameBounds = _startNewGame.getGlobalBounds();
    float textX1 = (1920 - startNewGameBounds.width) / 2;
    _startNewGame.setPosition(textX1, 860.f);

    _gameNametext.setFont(_font);
    _gameNametext.setCharacterSize(36);
    _gameNametext.setFillColor(fillColor);
    _gameNametext.setOutlineColor(outlineColor);
    _gameNametext.setOutlineThickness(2.0f);
    _gameNametext.setString("NOM DE LA PARTIE :");
    sf::FloatRect gameNametextBounds = _gameNametext.getGlobalBounds();
    float textX2 = (1920 - gameNametextBounds.width) / 2;
    _gameNametext.setPosition(textX2, 250.f);

    _inputGameName.setFont(_font);
    _inputGameName.setCharacterSize(26);
    _inputGameName.setFillColor(sf::Color(0x241C1CFF));
    _inputGameName.setOutlineColor(sf::Color(0x7D7D7DFF));
    _inputGameName.setOutlineThickness(2.0f);
    _inputGameName.setPosition(725.f, 310.f);
    _inputGameName.setString("Entrer ici le nom de la partie");

    _gameLeveltext.setFont(_font);
    _gameLeveltext.setCharacterSize(36);
    _gameLeveltext.setFillColor(fillColor);
    _gameLeveltext.setOutlineColor(outlineColor);
    _gameLeveltext.setOutlineThickness(2.0f);
    _gameLeveltext.setString("NIVEAU DE DIFFICULTE :");
    sf::FloatRect gameLeveltextBounds = _gameLeveltext.getGlobalBounds();
    float textX3 = (1920 - gameLeveltextBounds.width) / 2;
    _gameLeveltext.setPosition(textX3, 400.f);

    _level1Text.setFont(_font);
    _level1Text.setCharacterSize(26);
    _level1Text.setFillColor(fillColor);
    _level1Text.setOutlineColor(outlineColor);
    _level1Text.setOutlineThickness(2.0f);
    _level1Text.setString("1");
    _level1Text.setPosition(890.f, 460.f);

    _level2Text.setFont(_font);
    _level2Text.setCharacterSize(26);
    _level2Text.setFillColor(fillColor);
    _level2Text.setOutlineColor(outlineColor);
    _level2Text.setOutlineThickness(2.0f);
    _level2Text.setString("2");
    _level2Text.setPosition(940.f, 460.f);

    _level3Text.setFont(_font);
    _level3Text.setCharacterSize(26);
    _level3Text.setFillColor(fillColor);
    _level3Text.setOutlineColor(outlineColor);
    _level3Text.setOutlineThickness(2.0f);
    _level3Text.setString("3");
    _level3Text.setPosition(990.f, 460.f);

    _gamePlayertext.setFont(_font);
    _gamePlayertext.setCharacterSize(36);
    _gamePlayertext.setFillColor(fillColor);
    _gamePlayertext.setOutlineColor(outlineColor);
    _gamePlayertext.setOutlineThickness(2.0f);
    _gamePlayertext.setString("NOMBRE DE JOUEURS :");
    sf::FloatRect gameplayertextBounds = _gamePlayertext.getGlobalBounds();
    float textX4 = (1920 - gameplayertextBounds.width) / 2;
    _gamePlayertext.setPosition(textX4, 550.f);

    _p1Text.setFont(_font);
    _p1Text.setCharacterSize(26);
    _p1Text.setFillColor(fillColor);
    _p1Text.setOutlineColor(outlineColor);
    _p1Text.setOutlineThickness(2.0f);
    _p1Text.setString("1");
    _p1Text.setPosition(885.f, 610.f);

    _p2Text.setFont(_font);
    _p2Text.setCharacterSize(26);
    _p2Text.setFillColor(fillColor);
    _p2Text.setOutlineColor(outlineColor);
    _p2Text.setOutlineThickness(2.0f);
    _p2Text.setString("2");
    _p2Text.setPosition(925.f, 610.f);

    _p3Text.setFont(_font);
    _p3Text.setCharacterSize(26);
    _p3Text.setFillColor(fillColor);
    _p3Text.setOutlineColor(outlineColor);
    _p3Text.setOutlineThickness(2.0f);
    _p3Text.setString("3");
    _p3Text.setPosition(965.f, 610.f);

    _p4Text.setFont(_font);
    _p4Text.setCharacterSize(26);
    _p4Text.setFillColor(fillColor);
    _p4Text.setOutlineColor(outlineColor);
    _p4Text.setOutlineThickness(2.0f);
    _p4Text.setString("4");
    _p4Text.setPosition(1005.f, 610.f);

    _mapTitleText.setFont(_font);
    _mapTitleText.setCharacterSize(36);
    _mapTitleText.setFillColor(fillColor);
    _mapTitleText.setOutlineColor(outlineColor);
    _mapTitleText.setOutlineThickness(2.0f);
    _mapTitleText.setString("MAP CHOISIE :");
    sf::FloatRect mapTitleBounds = _mapTitleText.getGlobalBounds();
    float textX5 = (1920 - mapTitleBounds.width) / 2;
    _mapTitleText.setPosition(textX5, 700.f);

    _newGameValues.resetValues();

    _mapSelectedText.setFont(_font);
    _mapSelectedText.setCharacterSize(26);
    _mapSelectedText.setFillColor(fillColor);
    _mapSelectedText.setOutlineColor(outlineColor);
    _mapSelectedText.setOutlineThickness(2.0f);
    _mapSelectedText.setString(_newGameValues.mapList[0]);
    sf::FloatRect selectedMapBounds = _mapSelectedText.getGlobalBounds();
    float textX6 = (1920 - selectedMapBounds.width) / 2;
    _mapSelectedText.setPosition(textX6, 760.f);
    
    _nextMapArrow.setFont(_font);
    _nextMapArrow.setCharacterSize(26);
    _nextMapArrow.setFillColor(fillColor);
    _nextMapArrow.setOutlineColor(outlineColor);
    _nextMapArrow.setOutlineThickness(2.0f);
    _nextMapArrow.setString(">");
    float textX7 = (1920 / 2) + (selectedMapBounds.width / 2) + 25;
    _nextMapArrow.setPosition(textX7, 760.f);
    
    _prevMapArrow.setFont(_font);
    _prevMapArrow.setCharacterSize(26);
    _prevMapArrow.setFillColor(fillColor);
    _prevMapArrow.setOutlineColor(outlineColor);
    _prevMapArrow.setOutlineThickness(2.0f);
    _prevMapArrow.setString("<");
    float textX8 = (1920 / 2) - (selectedMapBounds.width / 2) - 40;
    _prevMapArrow.setPosition(textX8, 760.f);

    _startGame.setFont(_font);
    _startGame.setCharacterSize(36);
    _startGame.setFillColor(fillColor);
    _startGame.setOutlineColor(outlineColor);
    _startGame.setOutlineThickness(2.0f);
    _startGame.setString("Start Game");
    sf::FloatRect startGametextBounds = _startGame.getGlobalBounds();
    float textX9 = (1920 - startGametextBounds.width) / 2;
    _startGame.setPosition(textX9, 860.f);
}

void Menu::initializeRect() {
    sf::Color fillColor(0x241C1C80);
    sf::Color outlineColor(0x7D7D7D80);

    sf::Vector2f positions[9] = {
        sf::Vector2f(120, 400),
        sf::Vector2f(120, 500),
        sf::Vector2f(120, 600),
        sf::Vector2f(720, 400),
        sf::Vector2f(720, 500),
        sf::Vector2f(720, 600),
        sf::Vector2f(1320, 400),
        sf::Vector2f(1320, 500),
        sf::Vector2f(1320, 600)
    };

    sf::Vector2f textPositions[9] = {
        sf::Vector2f(120, 400),
        sf::Vector2f(120, 500),
        sf::Vector2f(120, 600),
        sf::Vector2f(720, 400),
        sf::Vector2f(720, 500),
        sf::Vector2f(720, 600),
        sf::Vector2f(1320, 400),
        sf::Vector2f(1320, 500),
        sf::Vector2f(1320, 600)
    };

    sf::Vector2f positionsGameName[9] = {
        sf::Vector2f(130, 425),
        sf::Vector2f(130, 525),
        sf::Vector2f(130, 625),
        sf::Vector2f(730, 425),
        sf::Vector2f(730, 525),
        sf::Vector2f(730, 625),
        sf::Vector2f(1330, 425),
        sf::Vector2f(1330, 525),
        sf::Vector2f(1330, 625)
    };

    sf::Vector2f positionActualPlayers[9] = {
        sf::Vector2f(520, 425),
        sf::Vector2f(520, 525),
        sf::Vector2f(520, 625),
        sf::Vector2f(1120, 425),
        sf::Vector2f(1120, 525),
        sf::Vector2f(1120, 625),
        sf::Vector2f(1720, 425),
        sf::Vector2f(1720, 525),
        sf::Vector2f(1720, 625)
    };

    sf::Vector2f positionsNbPlayersMax[9] = {
        sf::Vector2f(538, 425),
        sf::Vector2f(538, 525),
        sf::Vector2f(538, 625),
        sf::Vector2f(1138, 425),
        sf::Vector2f(1138, 525),
        sf::Vector2f(1138, 625),
        sf::Vector2f(1738, 425),
        sf::Vector2f(1738, 525),
        sf::Vector2f(1738, 625)
    };

    for (int i = 0; i < 9; i++) {
        sf::RectangleShape& rect = _rectSlots[i];
        rect.setSize(sf::Vector2f(480, 70));
        rect.setPosition(positions[i]);
        rect.setFillColor(fillColor);
        rect.setOutlineColor(outlineColor);
        rect.setOutlineThickness(2);

        sf::Text& txtGameName = _rectDataGameName[i];
        txtGameName.setFont(_font);
        txtGameName.setCharacterSize(24);
        txtGameName.setFillColor(fillColor);
        txtGameName.setOutlineColor(outlineColor);
        txtGameName.setOutlineThickness(1.0f);
        txtGameName.setString("NomDeLaGame");
        txtGameName.setPosition(positionsGameName[i]);
        
        sf::Text& txtNbPlayerMax = _rectDataPlayersMax[i];
        txtNbPlayerMax.setFont(_font);
        txtNbPlayerMax.setCharacterSize(24);
        txtNbPlayerMax.setFillColor(fillColor);
        txtNbPlayerMax.setOutlineColor(outlineColor);
        txtNbPlayerMax.setOutlineThickness(1.0f);
        txtNbPlayerMax.setString("/4");
        txtNbPlayerMax.setPosition(positionsNbPlayersMax[i]);
        
        sf::Text& txtPlayersWaiting = _rectDataNbPlayersWaiting[i];
        txtPlayersWaiting.setFont(_font);
        txtPlayersWaiting.setCharacterSize(24);
        txtPlayersWaiting.setFillColor(fillColor);
        txtPlayersWaiting.setOutlineColor(outlineColor);
        txtPlayersWaiting.setOutlineThickness(1.0f);
        txtPlayersWaiting.setString("2");
        txtPlayersWaiting.setPosition(positionActualPlayers[i]);
    }
}

void Menu::actualiseVariables()
{
    _time = _clock.getElapsedTime();
    _second = _time.asSeconds();
    _time2 = _clock2.getElapsedTime();
    _second2 = _time2.asSeconds();
}

void Menu::assignVariables(sf::RenderWindow &win)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(win);

    if (_menuPage == 0) {
        sf::FloatRect textBounds = _inputText.getGlobalBounds();
        float textX = (win.getSize().x - textBounds.width) / 2;
        _inputText.setPosition(textX, 400.f);
        
        sf::FloatRect textIpBounds = _inputIpText.getGlobalBounds();
        float ipX = (win.getSize().x - textIpBounds.width) / 2;
        _inputIpText.setPosition(ipX, 475.f);
        
        sf::FloatRect textPortBounds = _inputPortText.getGlobalBounds();
        float portX = (win.getSize().x - textPortBounds.width) / 2;
        _inputPortText.setPosition(portX, 550.f);
    
        if (_isTyping == false) {
            sf::FloatRect pseudoBounds = _inputText.getGlobalBounds();
            if (pseudoBounds.contains(sf::Vector2f(mousePosition))) {
                _inputText.setOutlineColor(sf::Color::White);
            } else {
                _inputText.setOutlineColor(sf::Color(0x7D7D7DFF));
            }

            sf::FloatRect playBounds = _playText.getGlobalBounds();
            if (playBounds.contains(sf::Vector2f(mousePosition))) {
                _playText.setOutlineColor(sf::Color::White);
            } else {
                _playText.setOutlineColor(sf::Color(0x7D7D7DFF));
            }

            if (textIpBounds.contains(sf::Vector2f(mousePosition))) {
                _inputIpText.setOutlineColor(sf::Color::White);
            } else {
                _inputIpText.setOutlineColor(sf::Color(0x7D7D7DFF));
            }

            if (textPortBounds.contains(sf::Vector2f(mousePosition))) {
                _inputPortText.setOutlineColor(sf::Color::White);
            } else {
                _inputPortText.setOutlineColor(sf::Color(0x7D7D7DFF));
            }
        }

        if (_userInput.empty() == true) {
            _inputText.setString("Entrer votre pseudo");
            _isSomethingWritePseudo = false;
        } else {
            _inputText.setString(_userInput);
        }

        if (_userIpInput.empty() == true) {
            _inputIpText.setString("Ip");
            _isSomethingWriteIp = false;
        } else {
            _inputIpText.setString(_userIpInput);
        }

        if (_userPortInput.empty() == true) {
            _inputPortText.setString("Port");
            _isSomethingWritePort = false;
        } else {
            _inputPortText.setString(_userPortInput);
        }
    } else if (_menuPage  ==  1) {
        bool isMouseOverRect = false;
        for (int i = 0; i < 9; i++) {
            sf::FloatRect rectBounds = _rectSlots[i].getGlobalBounds();
            if (rectBounds.contains(sf::Vector2f(mousePosition)) && !_isSettingsOpen && !_rectData[i].isNotEmpty) {
                _rectSlots[i].setOutlineColor(sf::Color::White);
                _newGameText.setPosition(_rectSlots[i].getPosition().x + _rectSlots[i].getSize().x / 2, (_rectSlots[i].getPosition().y + _rectSlots[i].getSize().y / 2) + 5);
                isMouseOverRect = true;
            } else {
                _rectSlots[i].setOutlineColor(sf::Color(0x7D7D7D80));
            }
            if (!isMouseOverRect) {
                _newGameText.setPosition(-1000.f, -1000.f);
            }
        }
        if (_isNewGameOpen) {
            sf::FloatRect logoutBounds = _startNewGame.getGlobalBounds();
            if (logoutBounds.contains(sf::Vector2f(mousePosition))) {
                _startNewGame.setOutlineColor(sf::Color::White);
            } else {
                _startNewGame.setOutlineColor(sf::Color(0x7D7D7DFF));
            }

            sf::FloatRect textBounds = _inputGameName.getGlobalBounds();
            float textX = (win.getSize().x - textBounds.width) / 2;
            _inputGameName.setPosition(textX, 310.f);
            sf::FloatRect selectedMapBounds = _mapSelectedText.getGlobalBounds();
            float textX7 = (1920 / 2) + (selectedMapBounds.width / 2) + 25;
            _nextMapArrow.setPosition(textX7, 760.f);
            float textX8 = (1920 / 2) - (selectedMapBounds.width / 2) - 40;
            _prevMapArrow.setPosition(textX8, 760.f);
            if (_userInputGameName.empty() == true) {
                _inputGameName.setString("Entrer ici le nom de la partie");
                _isSomethingWrite = false;
            } else {
                _inputGameName.setString(_userInputGameName);
            }

            if (!_isTyping) {
                sf::FloatRect pseudoBounds = _inputGameName.getGlobalBounds();
                sf::FloatRect lvl1TxtB = _level1Text.getGlobalBounds();
                sf::FloatRect lvl2TxtB = _level2Text.getGlobalBounds();
                sf::FloatRect lvl3TxtB = _level3Text.getGlobalBounds();
                sf::FloatRect p1TxtB = _p1Text.getGlobalBounds();
                sf::FloatRect p2TxtB = _p2Text.getGlobalBounds();
                sf::FloatRect p3TxtB = _p3Text.getGlobalBounds();
                sf::FloatRect p4TxtB = _p4Text.getGlobalBounds();
                sf::FloatRect next = _nextMapArrow.getGlobalBounds();
                sf::FloatRect prev = _prevMapArrow.getGlobalBounds();

                if (pseudoBounds.contains(sf::Vector2f(mousePosition))) {
                    _inputGameName.setOutlineColor(sf::Color::White);
                } else { 
                    _inputGameName.setOutlineColor(sf::Color(0x7D7D7DFF));
                }

                if (lvl1TxtB.contains(sf::Vector2f(mousePosition))) {
                    _level1Text.setOutlineColor(sf::Color::White);
                } else {
                    _level1Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.level == 1)
                        _level1Text.setOutlineColor(sf::Color::Green);
                }

                if (lvl2TxtB.contains(sf::Vector2f(mousePosition))) {
                    _level2Text.setOutlineColor(sf::Color::White);
                } else {
                    _level2Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.level == 2)
                        _level2Text.setOutlineColor(sf::Color::Yellow);
                }

                if (lvl3TxtB.contains(sf::Vector2f(mousePosition))) {
                    _level3Text.setOutlineColor(sf::Color::White);
                } else {
                    _level3Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.level == 3)
                        _level3Text.setOutlineColor(sf::Color::Red);
                }

                if (p1TxtB.contains(sf::Vector2f(mousePosition))) {
                    _p1Text.setOutlineColor(sf::Color::White);
                } else {
                    _p1Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.players == 1)
                        _p1Text.setOutlineColor(sf::Color::Blue);
                }

                if (p2TxtB.contains(sf::Vector2f(mousePosition))) {
                    _p2Text.setOutlineColor(sf::Color::White);
                } else {
                    _p2Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.players == 2)
                        _p2Text.setOutlineColor(sf::Color::Blue);
                }

                if (p3TxtB.contains(sf::Vector2f(mousePosition))) {
                    _p3Text.setOutlineColor(sf::Color::White);
                } else {
                    _p3Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.players == 3)
                        _p3Text.setOutlineColor(sf::Color::Blue);
                }

                if (p4TxtB.contains(sf::Vector2f(mousePosition))) {
                    _p4Text.setOutlineColor(sf::Color::White);
                } else {
                    _p4Text.setOutlineColor(sf::Color(0x7D7D7DFF));
                    if (_newGameValues.players == 4)
                        _p4Text.setOutlineColor(sf::Color::Blue);
                }

                if (next.contains(sf::Vector2f(mousePosition))) {
                    _nextMapArrow.setOutlineColor(sf::Color::White);
                } else {
                    _nextMapArrow.setOutlineColor(sf::Color(0x7D7D7DFF));
                }

                if (prev.contains(sf::Vector2f(mousePosition))) {
                    _prevMapArrow.setOutlineColor(sf::Color::White);
                } else {
                    _prevMapArrow.setOutlineColor(sf::Color(0x7D7D7DFF));
                }
            }
        }
    }
}

void Menu::displayStringInBox(sf::RenderWindow& window, const std::string& text, std::size_t x, std::size_t y, std::size_t width, std::size_t height) 
{
    // Define the box dimensions
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(width, height)); // Adjust the width and height as needed
    sf::Color fillColor(0x241C1C80);
    box.setFillColor(fillColor);
    sf::Color outlineColor(0x7D7D7D80);
    box.setOutlineColor(outlineColor);
    box.setOutlineThickness(2);
    box.setPosition(sf::Vector2f(x, y));

    sf::Text displayText;
    displayText.setFont(_font);
    displayText.setString(text);
    displayText.setCharacterSize(24); // Adjust the character size as needed
    displayText.setFillColor(outlineColor);
    
    // Center the text within the box
    sf::FloatRect textBounds = displayText.getLocalBounds();
    displayText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    displayText.setPosition(x + box.getSize().x / 2.0f, y + box.getSize().y / 2.0f);

    // Draw the box and text to the window
    window.draw(box);
    window.draw(displayText);
}

void Menu::drawVariables(sf::RenderWindow &win, std::size_t roomCreating)
{
    if (_menuPage < 3)
        win.draw(_infosLobbySprite);
    if (_menuPage == 0) {
       win.draw(_inputText);
       win.draw(_playText);
       win.draw(_inputIpText);
       win.draw(_inputPortText);
    } else if (_menuPage == 1) {
        for (int i = 0; i < 9; i++) {
            win.draw(_rectSlots[i]);
            if (_rectData[i].isNotEmpty) {
                win.draw(_rectDataGameName[i]);
                win.draw(_rectDataPlayersMax[i]);
                win.draw(_rectDataNbPlayersWaiting[i]);
            }
        }
        win.draw(_newGameText);
        win.draw(_lobbiesText);
        if (_isNewGameOpen) {
            win.draw(_newGameRectBackground);
            if (!_rectData[roomCreating].isNotEmpty) {
                win.draw(_startNewGame);
                win.draw(_gameNametext); 
                win.draw(_inputGameName);
                win.draw(_gameLeveltext);
                win.draw(_level1Text);
                win.draw(_level2Text);
                win.draw(_level3Text);
                win.draw(_gamePlayertext);
                win.draw(_p1Text);
                win.draw(_p2Text);
                win.draw(_p3Text);
                win.draw(_p4Text);
                win.draw(_mapTitleText);
                win.draw(_mapSelectedText);
                win.draw(_nextMapArrow);
                win.draw(_prevMapArrow);
            } else {
                std::size_t i = 0;
                for (const std::string& participant : participants) {
                    displayStringInBox(win, participant, 200, 280 + i, 1000, 50);
                    i += 50;
                }
                displayStringInBox(win, _rectDataGameMap[roomCreating], 1220, 280, 500, 500);
                win.draw(_startGame);
            }
        }
    }
}

void Menu::clockGestion(sf::Sprite &_backgroundSprite1, sf::Sprite &_backgroundSprite2, std::size_t as)
{
    if (_second > 0.001) {
        _backgroundSprite1.move(sf::Vector2f(-1.0f, 0.0f));
        _backgroundSprite2.move(sf::Vector2f(-1.0f, 0.0f));
        sf::Vector2f posBGS1 = _backgroundSprite1.getPosition();
        sf::Vector2f posBGS2 = _backgroundSprite2.getPosition();
        if (as == 3) {
            if (posBGS1.x < -8118)
                _backgroundSprite1.setPosition(8117, 0);
            if (posBGS2.x < -8118)
                _backgroundSprite2.setPosition(8117, 0);
        } else {
        if (posBGS1.x < -2160)
            _backgroundSprite1.setPosition(2159, 0);
        if (posBGS2.x < -2160)
            _backgroundSprite2.setPosition(2159, 0);

        }
        _clock.restart();
    }
    if (_isTyping == true) {
        if (_second2 > 0.6) {
            if (_switchTyping == 0) {
                if (_isTypingPseudo)
                    _inputText.setOutlineColor(sf::Color::White);
                else if (_isTypingIp)
                    _inputIpText.setOutlineColor(sf::Color::White);
                else if (_isTypingPort)
                    _inputPortText.setOutlineColor(sf::Color::White);
                _inputGameName.setOutlineColor(sf::Color::White);
                _switchTyping = 1;
            } else {
                if (_isTypingPseudo)
                    _inputText.setOutlineColor(sf::Color(0x7D7D7DFF));
                else if (_isTypingIp)
                    _inputIpText.setOutlineColor(sf::Color(0x7D7D7DFF));
                else if (_isTypingPort)
                    _inputPortText.setOutlineColor(sf::Color(0x7D7D7DFF));
                _inputGameName.setOutlineColor(sf::Color(0x7D7D7DFF));
                _switchTyping = 0;
            }
            _clock2.restart();
        }
    }
}

void Menu::getInput(sf::Event windowEvent)
{
    if (_menuPage == 0) {
        if (_isTypingPseudo) {
            if (windowEvent.text.unicode < 128) {
                if (_isSomethingWritePseudo == false) {
                    _userInput.clear();
                    _isSomethingWritePseudo = true;
                }
                if (windowEvent.text.unicode == '\b' && !_userInput.empty()) {
                    _userInput.pop_back();
                } else if (windowEvent.text.unicode != '\b' && _userInput.length() < 20) {
                    _userInput += static_cast<char>(windowEvent.text.unicode);
                }
            }
        } else if (_isTypingIp) {
            if (windowEvent.text.unicode < 128) {
                if (_isSomethingWriteIp == false) {
                    _userIpInput.clear();
                    _isSomethingWriteIp = true;
                }
                if (windowEvent.text.unicode == '\b' && !_userIpInput.empty()) {
                    _userIpInput.pop_back();
                } else if (windowEvent.text.unicode != '\b' && _userIpInput.length() < 20) {
                    _userIpInput += static_cast<char>(windowEvent.text.unicode);
                }
            }
        } else if (_isTypingPort) {
            if (windowEvent.text.unicode < 128) {
                if (_isSomethingWritePort == false) {
                    _userPortInput.clear();
                    _isSomethingWritePort = true;
                }
                if (windowEvent.text.unicode == '\b' && !_userPortInput.empty()) {
                    _userPortInput.pop_back();
                } else if (windowEvent.text.unicode != '\b' && _userPortInput.length() < 20) {
                    _userPortInput += static_cast<char>(windowEvent.text.unicode);
                }
            }
        }
    } else if (_menuPage == 1) {
        if (windowEvent.text.unicode < 128) {
            if (_isSomethingWrite == false) {
                _userInputGameName.clear();
                _isSomethingWrite = true;
            }
            if (windowEvent.text.unicode == '\b' && !_userInputGameName.empty()) {
                _userInputGameName.pop_back();
            } else if (windowEvent.text.unicode != '\b' && _userInputGameName.length() < 20) {
                _userInputGameName += static_cast<char>(windowEvent.text.unicode);
            }
            _newGameValues.name = _userInputGameName;
        }
    }
}

void Menu::goNextPage()
{
    if (!_userInput.empty()) {
        _menuPage = 1;
    }
}

void Menu::receiveLobbies(std::string data)
{
    if (data.substr(0, 3) == "240") {
        data = data.substr(4);
        std::vector<std::string> parts;
        std::istringstream ss(data);
        std::string part;

        while (std::getline(ss, part, '/')) {
            parts.push_back(part);
        }

        for (const std::string& p : parts) {
            std::istringstream iss(p);

            std::string room;
            std::size_t IdRect;
            std::string name;
            std::string NombreJoueursActuels;
            std::size_t difficulty;
            std::string NombreJoueursMax;
            std::string map;

            iss >> room >> IdRect;
            if (iss.peek() == ':')
                iss.ignore();
            iss >> name >> difficulty >> NombreJoueursMax >> NombreJoueursActuels >> map;
            _lobbiesPlayersMax[IdRect] = std::stoi(NombreJoueursMax);
            _rectDataGameName[IdRect].setString(name);
            _rectDataGameMap[IdRect].assign(map);
            _rectDataNbPlayersWaiting[IdRect].setString(NombreJoueursActuels);
            _rectDataPlayersMax[IdRect].setString("/" + NombreJoueursMax);
            if (difficulty == 1) {
                _rectDataGameName[IdRect].setOutlineColor(sf::Color::Green);
                _rectDataNbPlayersWaiting[IdRect].setOutlineColor(sf::Color::Green);
                _rectDataPlayersMax[IdRect].setOutlineColor(sf::Color::Green);
            } else if (difficulty == 2) {
                _rectDataGameName[IdRect].setOutlineColor(sf::Color::Yellow);
                _rectDataNbPlayersWaiting[IdRect].setOutlineColor(sf::Color::Yellow);
                _rectDataPlayersMax[IdRect].setOutlineColor(sf::Color::Yellow);
            } else if (difficulty == 3) {
                _rectDataGameName[IdRect].setOutlineColor(sf::Color::Red);
                _rectDataNbPlayersWaiting[IdRect].setOutlineColor(sf::Color::Red);
                _rectDataPlayersMax[IdRect].setOutlineColor(sf::Color::Red);
            }

            if (name != "Null") {
                _rectData[IdRect].isNotEmpty = true;
                _rectDataNbPlayersWaiting[IdRect].setString(NombreJoueursActuels);
            }
        }
    }
}

void Menu::receiveParticipants(std::string data)
{
    if (data.substr(0, 3) == "250") {
        data = data.substr(4);
        std::vector<std::string> parts;
        std::istringstream ss(data);
        std::string part;
        participants.clear();
        while (std::getline(ss, part, '/'))
            participants.push_back(part);
    }
}

Menu::~Menu()
{
}
