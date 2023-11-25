/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "System/RenderSystem.hpp"
#include "../src/Entity/NewGame.cpp"
#include "../src/RectData.cpp"

class Menu {
    public:
        Menu();
        ~Menu();

        void getInput(sf::Event windowEvent);
        void goNextPage();
        void actualiseVariables();
        void drawVariables(sf::RenderWindow &win, std::size_t roomCreating);
        void assignVariables(sf::RenderWindow &win);
        void clockGestion(sf::Sprite &_backgroundSprite1, sf::Sprite &_backgroundSprite2, std::size_t as);
        void displayStringInBox(sf::RenderWindow& window, const std::string& text, std::size_t x, std::size_t y, std::size_t width, std::size_t height);
        void initializeRect();
        void receiveLobbies(std::string data);
        void receiveParticipants(std::string data);

        std::string _name;
        int         _id;
        sf::Clock   _clock;
        sf::Time    _time;
        float       _second;
        sf::Clock   _clock2;
        sf::Time    _time2;
        float       _second2;
        std::string _userInput;
        std::string _userIpInput;
        std::string _userPortInput;
        bool        _isSomethingWrite;
        bool        _isSomethingWritePseudo;
        bool        _isSomethingWriteIp;
        bool        _isSomethingWritePort;
        bool        _isTyping;
        int         _menuPage;
        bool        _isTypingPseudo;
        bool        _isTypingIp;
        bool        _isTypingPort;

        sf::Font            _font;
        int                 _switchTyping;

        sf::Texture         _backgroundTexture;
        sf::Texture         _infosLobbyTexture;
        sf::Sprite          _infosLobbySprite;

        sf::Text            _inputText;
        sf::Text            _playText;
        sf::Text            _inputIpText;
        sf::Text            _inputPortText;

        sf::RectangleShape  _rectSlots[9];
        sf::Text  _rectDataGameName[9];
        sf::Text  _rectDataNbPlayersWaiting[9];
        sf::Text  _rectDataPlayersMax[9];
        std::string  _rectDataGameMap[9];
        std::size_t _lobbiesPlayersMax[9];
        RectData _rectData[9];
        sf::Text            _newGameText;
        sf::Text            _lobbiesText;
        bool                _isSettingsOpen;

        bool                _isNewGameOpen;
        sf::RectangleShape  _newGameRectBackground;
        sf::Text            _startNewGame;
        sf::Text            _gameNametext;
        sf::Text            _inputGameName;
        std::string         _userInputGameName;
        sf::Text            _gameLeveltext;
        sf::Text            _level1Text;
        sf::Text            _level2Text;
        sf::Text            _level3Text;
        sf::Text            _gamePlayertext;
        sf::Text            _p1Text;
        sf::Text            _p2Text;
        sf::Text            _p3Text;
        sf::Text            _p4Text;
        sf::Text            _mapTitleText;
        sf::Text            _mapSelectedText;
        NewGame             _newGameValues;
        sf::Text            _nextMapArrow;
        sf::Text            _prevMapArrow;

        std::vector<std::string> participants;
        sf::Text    _inputChatText;
        std::string _userInputChatText;

        sf::Text _startGame;


    protected:
    private:
};

#endif /* !MENU_HPP_ */