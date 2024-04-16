/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <Graph/Game.hpp>

Game::Game(std::string assetsPath)
: parser("src/Graph/GameConfig.json")
{
    _assetsPath = assetsPath;

    this->parser.GetJsonInfos("Config", this->parser._parsedData);
    _serverIp = std::to_string(this->parser._parsedData["DefaultserverIP"]["ipPart1"])
        + "." + std::to_string(this->parser._parsedData["DefaultserverIP"]["ipPart2"])
        + "." + std::to_string(this->parser._parsedData["DefaultserverIP"]["ipPart3"])
        + "." + std::to_string(this->parser._parsedData["DefaultserverIP"]["ipPart4"]);

    client = std::make_unique<ClientConnection>(_serverIp, 8888);

    sf::VideoMode mode(
        { static_cast<unsigned int>(800), static_cast<unsigned int>(600) });
    window.create(mode, "R-type Client");
    window.setFramerateLimit(60);

    if (!font.loadFromFile(_assetsPath + "magical_childhood/MagicalChildhood.ttf")) {
        throw Error("Error loading arial.ttf");
    }

    audioCreation();

    _audio->getAudio("menu")->play();

    this->objectManager = std::make_shared<ObjectManager>(assetsPath + "sprites/TilesMap.png");
    this->objectManager->updateTime = sf::seconds(0.2f);

    this->planetsManager = std::make_shared<ObjectManager>(assetsPath + "sprites/planetBackground.png");
    this->planetsManager->updateTime = sf::seconds(0.2f);
    this->planetsManager->createObject("planet1", 1);

    this->HUDManager = std::make_shared<ObjectManager>(assetsPath + "sprites/TilesMap.png");
    this->HUDManager->updateTime = sf::seconds(0.2f);

    this->parser.GetJsonInfos("Color", this->parser._parsedData);
    this->buttonColor = sf::Color(this->parser._parsedData["Button"]["red"],
        this->parser._parsedData["Button"]["green"],
        this->parser._parsedData["Button"]["blue"]);
    this->inputButtonColor = sf::Color(this->parser._parsedData["InputButton"]["red"],
        this->parser._parsedData["InputButton"]["green"],
        this->parser._parsedData["InputButton"]["blue"]);

    addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 50), sf::Text("Create Lobby", font, 15), buttonColor));
    addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 200), sf::Text("Join Lobby", font, 20), buttonColor));
    inputButton = std::make_shared<InputButton>(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 350), sf::Text("", font, 15), inputButtonColor);
}

Game::~Game() { }

void Game::audioCreation()
{
    _audio = std::make_unique<AudioManager>(_assetsPath);

    _audio->createAudio("menu", AudioType::Music, "menuSound.ogg");
    _audio->createAudio("game", AudioType::Music, "gameSound.ogg");
    _audio->createAudio("win", AudioType::Music, "winMusic.wav");
    _audio->createAudio("boss", AudioType::Music, "winMusic.wav");
    _audio->createAudio("lose", AudioType::Music, "loseMusic.ogg");

    _audio->createAudio("button", AudioType::SoundEffect, "buttonSound.ogg");
    _audio->createAudio("shoot", AudioType::SoundEffect, "shootSound.ogg");
    _audio->createAudio("explosion", AudioType::SoundEffect, "explosion.ogg");
    _audio->createAudio("newLevel", AudioType::SoundEffect, "levelSucceed.wav");
    _audio->createAudio("powerUp", AudioType::SoundEffect, "powerUp.ogg");
}

void Game::addButtons(Button button)
{
    button._RectShape.setPosition(button._pos.x, button._pos.y);
    buttons.push_back(std::make_shared<Button>(button));
}

sf::Text Game::createText(std::string str, sf::Vector2f pos) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);

    this->parser.GetJsonInfos("Color", this->parser._parsedData);

    text.setFillColor(sf::Color(this->parser._parsedData["Text"]["red"],
        this->parser._parsedData["Text"]["green"],
        this->parser._parsedData["Text"]["blue"]));
    text.setPosition(pos.x, pos.y);
    text.setCharacterSize(20);
    return text;
}

void Game::removeButton(size_t index)
{
    if (!buttons.empty()) {
        buttons.erase(buttons.begin() + index);
    }
}

void Game::handleKeyPress(const sf::Event& event) {
    auto it = keyMappings.find(event.key.code);

    if (it != keyMappings.end() && !it->second.second.isPressed) {
        it->second.first();
        it->second.second.clock.restart();
        it->second.second.isPressed = true;
    }
}

void Game::handleKeyRelease(const sf::Event& event) {
    auto it = keyMappings.find(event.key.code);
    if (it != keyMappings.end()) {
        PressDuration = (int)it->second.second.clock.getElapsedTime().asSeconds();

        if (PressDuration >= 5) {
            PressDuration = 4;
        }
        it->second.second.isPressed = false;
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            client.get()->sendCancelMoveY();
        if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D)
            client.get()->sendCancelMoveX();
        if (event.key.code == sf::Keyboard::Space) {
            keyPressDuration[PressDuration]();
            if (gameState == GameState::Playing)
                _audio->getAudio("shoot")->play();
        }
    }
}

void Game::stop()
{
    _audio->getAudio("menu")->stop();
    _audio->getAudio("game")->stop();
    _audio->getAudio("win")->stop();
    _audio->getAudio("lose")->stop();
    _audio->getAudio("boss")->stop();
    window.close();
    client->sendLogout();
}

void Game::processEvents()
{
    _ctrlC.checkCtrlCPressed();
    if (_ctrlC.ctrlCPressed == true) {
        stop();
        return;
    }
    if (keyMappings[sf::Keyboard::Space].second.isPressed) {
        int id = PlayersID[std::stoi(client->_myID)];
        HUDManager->updateStatBar(whoiam, keyMappings[sf::Keyboard::Space].second.clock.getElapsedTime().asSeconds(), "power");
    }
    while (window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {
            stop();
            return;
        }
        if (gameState < GameState::SpectateState) {
            if (_event.type == sf::Event::KeyPressed) {
                handleKeyPress(_event);
            } else if (_event.type == sf::Event::KeyReleased) {
                handleKeyRelease(_event);
            }
        }
    }
}

void Game::parseMsg(std::string msg)
{
    std::istringstream iss(msg);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
        std::istream_iterator<std::string>());

    if (results.size() == 0) {
        return;
    }

    if (results[0] == "12") {
        for (int i = 1; i < results.size(); i += 2) {
            PlayersID[std::stoi(results[i + 1])] = std::stoi(results[i]);
        }
        joinLobby();
    }
    if (results[0] == "13") {
        stop();
    }

    if (results[0] == "20") {
        for (int i = 1; i < results.size(); i += 3) {
            updateData[std::stoi(results[i])] = { std::stoi(results[i + 1]), std::stoi(results[i + 2]) };
        }
    }

    if (results[0] == "90") {
        if (whoiam == -1) {
            whoiam = std::stoi(results[1]);
            client->_myID = std::to_string(whoiam);
        }
    }

    if (results[0] == "36") {
        int playerId = -1;

        for (int i = 1; i < results.size(); i += 4) {
            int entityId = std::stoi(results[i]);
            int playerTextureRectX = std::stoi(results[i + 1]);
            int playerTextureRectY = std::stoi(results[i + 2]);
            type playerType = static_cast<type>(std::stoi(results[i + 3]));

            if (std::stoi(results[i + 3]) == player) {
                playerId = PlayersID[entityId];
                HUDManager.get()->createObject("HUD" + std::to_string(playerId), entityId);
                this->objectManager.get()->setTextureRect(entityId, playerTextureRectX, playerTextureRectY, playerType, playerId);
            } else {
                this->objectManager.get()->setTextureRect(entityId, playerTextureRectX, playerTextureRectY, playerType, 0);
            }
        }
    }
    if (results[0] == "37") {
        for (int i = 1; i < results.size(); i += 4) {
            this->objectManager.get()->setHealth(std::stoi(results[i]), std::stoi(results[i + 1]));
            this->HUDManager.get()->updateStatBar(std::stoi(results[i]), std::stoi(results[i + 1]), "health");
        }
    }
    if (results[0] == "40") {
        this->objectManager.get()->removeObject(std::stoi(results[1]));
        this->HUDManager.get()->updateStatBar(std::stoi(results[1]), 0, "health");
        this->HUDManager.get()->removeObject(std::stoi(results[1]));
        _audio->getAudio("explosion")->play();
        if (results[1] == client->_myID) {
            this->HUDManager.get()->updateStatBar(std::stoi(client->_myID), 0, "health");
            client->sendPlayerDisconnect();
            gameState = GameState::SpectateState;
        }
    }
    if (results[0] == "41") {
        this->objectManager.get()->removeObject(std::stoi(results[1]));
        // _audio->getAudio("explosion")->play(); //? work but not good for ears, try it if you want
    }
    if (results[0] == "60") {
        _gameLevel = 0;
    }
    if (results[0] == "61") {
        _gameLevel = 1;
    }
    if (results[0] == "62") {
        _gameLevel = 2;
       _audio->getAudio("newLevel")->play();
    }
    if (results[0] == "63") {
        _gameLevel = 3;
       _audio->getAudio("newLevel")->play();
    }
    if (results[0] == "64") {
        _gameLevel = 4;
       _audio->getAudio("boss")->play();
        _audio->getAudio("game")->stop();
       _audio->getAudio("newLevel")->play();
    }
    if (results[0] == "68") {
        gameState = GameState::LoseState;
        removeButton(0);
        removeButton(0);
        _audio->getAudio("game")->stop();
        _audio->getAudio("lose")->play();
        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 350), sf::Text("Quit", font, 15), sf::Color::Red));
        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(450, 350), sf::Text("Retry", font, 20), sf::Color::Cyan));
        score = results[1];
        _bestScore = std::stoi(results[2]);
    }
    if (results[0] == "69") {
        gameState = GameState::WinState;
        removeButton(0);
        removeButton(0);
        _audio->getAudio("game")->stop();
        _audio->getAudio("win")->play();
        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 350), sf::Text("Quit", font, 15), sf::Color::Red));
        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(450, 350), sf::Text("Retry", font, 20), sf::Color::Cyan));
        score = results[1];
        _bestScore = std::stoi(results[2]);
    }
    if (results[0] == "70") {
        score = results[1];
        if (scoreLvl == 1 && ((_gameLevel == 0 && std::stoi(score) >= 100 && std::stoi(score) < 300) || _gameLevel == 2)) {
            scoreLvl = 2;
            _audio->getAudio("powerUp")->play();
        }
        if (scoreLvl != 3 && ((_gameLevel == 0 && std::stoi(score) >= 300) || _gameLevel == 3)) {
            scoreLvl = 3;
            _audio->getAudio("powerUp")->play();
        }
    }
    if (results[0] == "35") {
        _audio->getAudio("shoot")->play();
    }
}

void Game::update(float deltaTime)
{
    std::string text = (gameState == GameState::SpectateState) ? "Spectator Mode\n" : "";
    sf::Vector2f position((gameState == GameState::SpectateState) ? 400 : 500, 50);

    if (_gameLevel == 0)
        text += "infinite mode";
    else if (_gameLevel == -1)
        text += "Waiting";
    else if (_gameLevel == 4)
        text += "Boss level";
    else
        text += "level : " + std::to_string(_gameLevel);
    textLevel = createText(text, position);

    text = "Score = " + score;
    position = sf::Vector2f(50, 50);
    textScore = createText(text, position);

    parseMsg(client.get()->listener());
    this->objectManager.get()->updateObjects(deltaTime, updateData);
    updateData.clear();
}

void Game::render()
{
    this->objectManager.get()->renderObjects(window);
    this->HUDManager.get()->renderObjects(window);
    this->window.draw(this->textLevel);
    this->window.draw(this->textScore);
    window.display();
}

void Game::menuState()
{
    processEvents();

    if (buttons[0].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("button")->play();
        gameState = GameState::LobbyCreation;

        this->parser.GetJsonInfos("Color", this->parser._parsedData);

        buttons[0]->_RectShape.setFillColor(sf::Color(this->parser._parsedData["ClickedButton"]["red"],
            this->parser._parsedData["ClickedButton"]["green"],
            this->parser._parsedData["ClickedButton"]["blue"]));

        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(450, 50), sf::Text("Create infiny Lobby", font, 15), buttonColor));
        addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(450, 200), sf::Text("Create level Lobby", font, 15), buttonColor));
    } else if (buttons[1].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("button")->play();
        client.get()->_port = 4444;
        client.get()->sendLobbyJoin();
        client.get()->_port = 8888;
    }

    window.clear(sf::Color(0, 0, 0));

    for (auto button : buttons) {
        button.get()->draw(window);
    }
    inputButton.get()->handleInputs(_event);
    client.get()->setServerIp(inputButton.get()->clientInput);
    inputButton.get()->draw(window);

    this->planetsManager.get()->renderObjects(window);

    parseMsg(client.get()->listener());
    window.display();
}

void Game::joinLobby()
{
    client.get()->_port = 4444;
    gameState = GameState::Playing;
    _audio->getAudio("menu")->stop();
    _audio->getAudio("game")->play();
}

void Game::lobbyCreation()
{
    processEvents();

    if (buttons[1].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("button")->play();
        removeButton(2);
        removeButton(2);
        client.get()->_port = 4444;
        client.get()->sendLobbyJoin();
        client.get()->_port = 8888;
    } else if (buttons[2].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("button")->play();
        client.get()->_port = 8888;
        client.get()->sendLobbyInfCreation();
        client.get()->listener();
        removeButton(2);
        removeButton(2);
        buttons[0]->_RectShape.setFillColor(buttons[0]->_defaultColor);
        gameState = GameState::StartMenu;
    } else if (buttons[3].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("button")->play();
        client.get()->_port = 8888;
        client.get()->sendLobbyLvlCreation();
        client.get()->listener();
        removeButton(2);
        removeButton(2);
        buttons[0]->_RectShape.setFillColor(buttons[0]->_defaultColor);
        gameState = GameState::StartMenu;
    }

    window.clear(sf::Color(0, 0, 0));

    for (auto button : buttons) {
        button.get()->draw(window);
    }
    this->planetsManager.get()->renderObjects(window);
    parseMsg(client.get()->listener());
    window.display();
}

void Game::playingState()
{
    sf::Time deltaTime = clock.restart();
    timeSinceLastUpdate += deltaTime;

    processEvents();

    if (timeSinceLastUpdate > timePerFrame) {
        timeSinceLastUpdate = sf::Time::Zero;
    }
    update(timePerFrame.asSeconds());
    window.clear(sf::Color(0, 0, 0));
    this->planetsManager.get()->renderObjects(window);
    render();
}

void Game::spectatorMode()
{
    sf::Time deltaTime = clock.restart();
    timeSinceLastUpdate += deltaTime;

    processEvents();

    if (timeSinceLastUpdate > timePerFrame) {
        timeSinceLastUpdate = sf::Time::Zero;
    }
    update(timePerFrame.asSeconds());
    window.clear(sf::Color(0, 0, 0));
    this->planetsManager.get()->renderObjects(window);
    render();
}

void Game::retry()
{
    client->sendRetry();
    gameState = GameState::StartMenu;
    _audio->getAudio("menu")->play();
    removeButton(0);
    removeButton(0);
    addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 50), sf::Text("Create Lobby", font, 15), buttonColor));
    addButtons(Button(sf::RectangleShape(sf::Vector2f(300, 100)), sf::Vector2f(50, 200), sf::Text("Join Lobby", font, 20), buttonColor));
    clock.restart();
    timerClock.restart();
    shootClock.restart();
    timeSinceLastUpdate = sf::Time::Zero;
    _gameLevel = -1;
    objectManager.reset();
    HUDManager.reset();
    updateData.clear();
    client.reset();
    this->objectManager = std::make_shared<ObjectManager>(_assetsPath + "sprites/TilesMap.png");
    this->objectManager->updateTime = sf::seconds(0.2f);
    this->HUDManager = std::make_shared<ObjectManager>(_assetsPath + "sprites/TilesMap.png");
    this->HUDManager->updateTime = sf::seconds(0.2f);
    client = std::make_unique<ClientConnection>(_serverIp, 8888);
    score = "0";
    scoreLvl = 1;
    whoiam = -1;
    seconds = 0;
    idPlayer.clear();
}

void Game::WinScene()
{
    std::string text = "YOU WIN\n";

    if (std::stoi(this->score) > this->_bestScore)
        text += "new high score : " + this->score;
    else
        text += "your score : " + this->score + "\nbest score : " + std::to_string(this->_bestScore);

    sf::Vector2f position(150, 100);
    textWinLose = createText(text, position);
    textWinLose.setCharacterSize(30);

    processEvents();

    if (buttons[0].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        client->sendPlayerDisconnect();
        _audio->getAudio("game")->stop();
        window.close();
    } else if (buttons[1].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("win")->stop();
        retry();
    }

    if (timeSinceLastUpdate > timePerFrame) {
        timeSinceLastUpdate = sf::Time::Zero;
    }
    update(timePerFrame.asSeconds());
    window.clear(sf::Color(0, 0, 0));

    for (auto button : buttons) {
        button.get()->draw(window);
    }
    this->planetsManager.get()->renderObjects(window);
    this->window.draw(this->textWinLose);
    window.display();
}

void Game::loseScene()
{
    std::string text = "YOU LOSE\n";

    if (std::stoi(this->score) > this->_bestScore)
        text += "new high score : " + this->score;
    else
        text += "your score : " + this->score + "\nbest score : " + std::to_string(this->_bestScore);
    sf::Vector2f position(150, 100);
    textWinLose = createText(text, position);
    textWinLose.setCharacterSize(30);

    processEvents();

    if (buttons[0].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        client->sendPlayerDisconnect();
        _audio->getAudio("game")->stop();
        window.close();
    } else if (buttons[1].get()->isClicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), _event, window)) {
        _audio->getAudio("lose")->stop();
        retry();
    }

    if (timeSinceLastUpdate > timePerFrame) {
        timeSinceLastUpdate = sf::Time::Zero;
    }
    update(timePerFrame.asSeconds());
    window.clear(sf::Color(0, 0, 0));

    for (auto button : buttons) {
        button.get()->draw(window);
    }
    this->planetsManager.get()->renderObjects(window);
    this->window.draw(this->textWinLose);
    window.display();
}

void Game::checkWindowSize()
{
    sf::Vector2u currentSize = window.getSize();
    sf::Vector2u minSize(800, 600);
    sf::Vector2u maxSize(1920, 1080);

    if (currentSize.x < minSize.x || currentSize.y < minSize.y ||
        currentSize.x > maxSize.x || currentSize.y > maxSize.y) {
        window.setSize(sf::Vector2u(
            std::max(minSize.x, std::min(currentSize.x, maxSize.x)),
            std::max(minSize.y, std::min(currentSize.y, maxSize.y))
        ));
    }
}

void Game::run()
{
    while (window.isOpen()) {
        checkWindowSize();
        switch (gameState) {
            case GameState::StartMenu:
                menuState();
                break;
            case GameState::LobbyCreation:
                lobbyCreation();
                break;
            case GameState::Playing:
                playingState();
                break;
            case GameState::SpectateState:
                spectatorMode();
                break;
            case GameState::WinState:
                WinScene();
                break;
            case GameState::LoseState:
                loseScene();
                break;
        }
    }
}
