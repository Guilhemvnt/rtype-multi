/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AISystem
*/

#include "Engine/Systems/AISystem.hpp"

AISystem::AISystem(EcsGameType gameType)
: parser("src/Engine/LevelConfig.json") {
    srand(time(NULL));
    _gameType = gameType;
    updateGameValues();

    this->parser.GetJsonInfos("Parameters", this->parser._parsedData);
    timerBetweenWaves = sf::seconds(this->parser._parsedData["Waves"]["timerBetweenWavesAsSeconde"]);
}

AISystem::~AISystem() { }

void AISystem::updateGameValues()
{
     switch (_gameType) {
        case EcsGameType::INF:
            this->parser.GetJsonInfos("Level", this->parser._parsedData);
            timerBetweenAI = sf::seconds(this->parser._parsedData["INF"]["timerBetweenAIAsMiliseconde"] / 1000);
            maxAI = this->parser._parsedData["INF"]["maxAI"];
            break;
        case EcsGameType::LVL1:
            this->parser.GetJsonInfos("Level", this->parser._parsedData);
            timerBetweenAI = sf::seconds(this->parser._parsedData["LVL1"]["timerBetweenAIAsMiliseconde"] / 1000);
            maxAI = this->parser._parsedData["LVL1"]["maxAI"];
            break;
        case EcsGameType::LVL2:
            this->parser.GetJsonInfos("Level", this->parser._parsedData);
            timerBetweenAI = sf::seconds(this->parser._parsedData["LVL2"]["timerBetweenAIAsMiliseconde"] / 1000);
            maxAI = this->parser._parsedData["LVL2"]["maxAI"];
            break;
        case EcsGameType::LVL3:
            this->parser.GetJsonInfos("Level", this->parser._parsedData);
            timerBetweenAI = sf::seconds(this->parser._parsedData["LVL3"]["timerBetweenAIAsMiliseconde"] / 1000);
            maxAI = this->parser._parsedData["LVL3"]["maxAI"];
            break;
        case EcsGameType::BOSS:
            this->parser.GetJsonInfos("Level", this->parser._parsedData);
            timerBetweenAI = sf::seconds(this->parser._parsedData["BOSS"]["timerBetweenAIAsMiliseconde"] / 1000);
            maxAI = 0;
            break;
        case EcsGameType::WIN:
            break;
        default:
            throw Error("Invalid game type");
    }
}

void AISystem::createAI(std::shared_ptr<EntityManager>& entityManager)
{
    Entity e = EntityFactory().createEntity("AI");
    auto r = (rand() % 10);
    e.getComponent<Position>().x = 805;
    e.getComponent<Position>().y = 60 * r;
    entityManager->createEntity(e);
    if (_gameType == EcsGameType::INF && e.id % 100 == 0) {
        Entity e = EntityFactory().createEntity("Boss");
        entityManager->createEntity(e);
    }
}

void AISystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    sf::Time elapsedTime = timer.getElapsedTime();

    if ( _gameType != EcsGameType::WIN && _gameType != EcsGameType::INF
    && ((_gameType != EcsGameType::BOSS || (bossIsSpawned && bossIsDead))
    && nbAidead >= maxAI)) {
        _gameType++;
        nbAI = 0;
        nbAidead = 0;
        std::cout << _gameType << " game started =====================" << std::endl;
        updateGameValues();
        timer.restart();
        return;
    }
    if (elapsedTime >= waitTimer) {
        if (_gameType == EcsGameType::BOSS) {
            if (bossIsSpawned == false) {
                bossIsSpawned = true;
                std::cout << "Boss created" << std::endl;
                Entity e = EntityFactory().createEntity("Boss");
                entityManager->createEntity(e);
            } else if (bossIsDead == false) {
                createAI(entityManager);
                maxAI += 1;
                waitTimer = timerBetweenAI;
            }
        } else if (nbAI < maxAI) {
            createAI(entityManager);
            nbAI++;
            waitTimer = timerBetweenAI;
        } else if (_gameType == EcsGameType::INF) {
            waitTimer = timerBetweenWaves;
            nbAI = 0;
        }
        timer.restart();
    }
}
