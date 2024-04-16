/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Engine
*/

#include <Engine/Engine.hpp>

Engine::Engine()
: parser("src/Engine/LevelConfig.json")
{
    gameObjects = std::make_shared<EntityManager>();
}

Engine::~Engine() { }

void Engine::start(EcsGameType gameType)
{
    _launchedGameType = gameType;

    if (_launchedGameType != EcsGameType::INF) {
        this->parser.GetJsonInfos("Parameters", this->parser._parsedData);
        int a = this->parser._parsedData["Game"]["startLevel"];
        std::cout << "Launched game type: " << a << std::endl;

        switch (a) {
            case 1:
                _launchedGameType = EcsGameType::LVL1;
                break;
            case 2:
                _launchedGameType = EcsGameType::LVL2;
                break;
            case 3:
                _launchedGameType = EcsGameType::LVL3;
                break;
            case 4:
                _launchedGameType = EcsGameType::BOSS;
                break;
            default:
                throw Error("Unknown level");
        }
    }

    std::cout << _launchedGameType << " engine started" << std::endl;

    _entityFactory = EntityFactory();
    _systems.push_back(std::make_shared<InputSystem>());
    _systems.push_back(std::make_shared<PowerupSystem>());
    _systems.push_back(std::make_shared<CollisionSystem>());
    _systems.push_back(std::make_shared<MvtSystem>());
    _systemAI = std::make_shared<AISystem>(_launchedGameType);
    _systems.push_back(_systemAI);
}

std::string Engine::restart(bool &startGame, int &lastEntityId) {
    if (_systemAI->_gameType == EcsGameType::WIN) {
        startGame = false;
        return "WIN";
    } else {
        lastEntityId = 0;
        if (_systemAI->_gameType == EcsGameType::INF) {
            return("60");
        } else {
            return("6" + std::to_string(static_cast<int>(_systemAI->_gameType)));
        }
    }
}

int Engine::addPlayer()
{
    int id = gameObjects->createEntity(_entityFactory.createEntity("Player"));
    if (gameObjects->hasEntity(id)) {
        gameObjects->getEntityById(id)->getComponent<Input>().isUpdated = true;
        gameObjects->getEntityById(id)->getComponent<Position>().y = 60 * id;
    }
    return id;
}

void Engine::clean()
{
    for (auto &entity : gameObjects->entitiesToDestroy) {
        gameObjects->destroyEntity(*entity);
    }
    gameObjects->entitiesToDestroy.clear();
    gameObjects->entitiesDamaged.clear();
}

void Engine::update(float deltaTime)
{
    for (auto &system : _systems) {
        system->update(gameObjects, deltaTime);
    }
}
