/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory.h>
#include <Graph/IScene.hpp>
#include <Graph/ObjectFactory.hpp>
#include <Graph/ObjectManager.hpp>
#include <Graph/AudioManager.hpp>
#include <Graph/InputButton.hpp>

#include <Client/ClientConnection.hpp>

#include <fstream>
#include <map>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <functional>

#include <CtrlC/CtrlC.hpp>
#include <JsonParser/JsonParser.hpp>

enum class GameState {
    //? state who need keyboard events
    StartMenu,
    Playing,
    LobbyCreation,

    //? state who don't need keyboard events
    SpectateState,
    WinState,
    LoseState
};

class Game : virtual public IScene {
public:
    Game(std::string assetsPath);
    ~Game();

    void run();

private:
    sf::Color buttonColor;
    sf::Color inputButtonColor;

    JsonParser parser;
    CtrlC _ctrlC;
    std::string _serverIp;

    sf::Event _event;
    GameState gameState = GameState::StartMenu;
    sf::Clock clock;
    sf::Clock timerClock;
    sf::Clock shootClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Font font;

    std::vector<std::shared_ptr<Button>> buttons;
    std::shared_ptr<InputButton> inputButton;
    sf::Mouse mouse;
    int seconds = 0;

    sf::RenderWindow window;
    std::shared_ptr<ObjectManager> objectManager;
    std::shared_ptr<ObjectManager> planetsManager;
    std::shared_ptr<ObjectManager> HUDManager;

    std::unique_ptr<ClientConnection> client;
    std::map<int, std::vector<int>> updateData;

    std::string _assetsPath;

    std::unique_ptr<AudioManager> _audio;

    int _gameLevel = -1;
    int scoreLvl = 1;
    sf::Text textLevel;
    sf::Text textWinLose;
    sf::Text textScore;
    std::vector<int> idPlayer;
    int whoiam = -1;

    std::string score = "0";

    struct KeyState {
        bool isPressed = false;
        sf::Clock clock;
    };
    std::map<int, int> PlayersID = {
        {0, -1},
        {1, -1},
        {2, -1},
        {3, -1},
    };
    int _bestScore;

    int PressDuration = 0;

    std::map<sf::Keyboard::Key, std::pair<std::function<void()>, KeyState>> keyMappings = {
        {sf::Keyboard::Z, { [&]() { client.get()->sendMoveUp(); }, KeyState()}},
        {sf::Keyboard::S, {[&]() { client.get()->sendMoveDown(); }, KeyState()}},
        {sf::Keyboard::Q, {[&]() { client.get()->sendMoveLeft(); }, KeyState()}},
        {sf::Keyboard::D, {[&]() { client.get()->sendMoveRight(); }, KeyState()}},
        {sf::Keyboard::Space, {[&]() {}, KeyState()}},
        {sf::Keyboard::Enter, {[&]() {client.get()->sendShootRocket();}, KeyState()}},
    };
    std::vector<std::function<void()>> keyPressDuration = {
        [&]() { client.get()->sendShootLevel0();},
        [&]() { client.get()->sendShootLevel1();},
        [&]() { client.get()->sendShootLevel2();},
        [&]() { client.get()->sendShootLevel3();},
        [&]() { client.get()->sendShootLevel4();},
    };

    void addButtons(Button);
    sf::Text createText(std::string, sf::Vector2f);
    void removeButton(size_t );
    void update(float deltaTime);
    void render();
    void processEvents();
    void handleKeyPress(const sf::Event& event);
    void handleKeyRelease(const sf::Event& event);
    void handleKeyTime();
    void spectatorMode();
    void playingState();
    void menuState();
    void lobbyCreation();
    void WinScene();
    void loseScene();
    void retry();
    void joinLobby();

    void checkWindowSize();
    void parseMsg(std::string msg);
    void stop();
    void audioCreation();
};

#endif /* !GAME_HPP_ */
