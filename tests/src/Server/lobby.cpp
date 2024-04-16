/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** lobby
*/

#include <SFML/System/Clock.hpp>
#include <Server/Lobby.hpp>
#include <iomanip>
#include <chrono>

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

void Lobby::sending(std::string msg) {
    sf::Packet sendPacket;
    sendPacket << msg.data();
    for (const auto &pair : computerIds) {
        const sf::IpAddress& ip = pair.second.first;
        unsigned short ip_port = pair.second.second;

        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        if (socket.send(sendPacket, ip, ip_port) != sf::Socket::Status::Done) {
            throw Error("Error sending message");
            return;
        }
    }
    for (const auto &pair : spectatorPlayers) {
        const sf::IpAddress& ip = pair.second.first;
        unsigned short ip_port = pair.second.second;

        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        if (socket.send(sendPacket, ip, ip_port) != sf::Socket::Status::Done) {
            throw Error("Error sending message");
            return;
        }
    }
}

Lobby::Lobby(unsigned short lport, EcsGameType gameType)
: port(lport), _launchedGameType(gameType), parser("src/Engine/LevelConfig.json")
{
    socket.setBlocking(false);
    if (socket.bind(lport) != sf::Socket::Status::Done) {
        throw Error("Already a lobby running");
    }

    this->parser.GetJsonInfos("Parameters", this->parser._parsedData);

    this->fps = this->parser._parsedData["Game"]["fps"];
    this->timePerFrame = sf::seconds(1.f/fps);

    this->score = this->parser._parsedData["Game"]["startScore"];
}

void Lobby::listening(void)
{
    _ctrlC.checkCtrlCPressed();
    if (_ctrlC.ctrlCPressed == true) {
        sendCloseLobby();
        start_game = false;
        closed = true;
        computerIds.clear();
        spectatorPlayers.clear();
        return;
    }

    bool bit = false;
    sf::Packet packetReceive;
    std::string msg;
    sf::Socket::Status status = socket.receive(packetReceive, this->sender, this->port);

    if (status == sf::Socket::Status::Disconnected) return;

    if (status != sf::Socket::Status::Done && status != sf::Socket::Status::NotReady) {
        std::cerr << "Error receiving message in lobby. Error code: " << status << " from ip " << this->sender << " on port " << this->port << std::endl;
        return;
    }

    if (status == sf::Socket::Status::NotReady) return;

    packetReceive >> msg;
    std::copy(msg.begin(), msg.end(), this->buffer);
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    for (const auto &pair : computerIds) {
        const sf::IpAddress& ip = pair.second.first;
        unsigned short ip_port = pair.second.second;

        bit = ((this->sender == ip && port == ip_port) ? true : false);
    }
    (((bit == false || computerIds.empty() == true) && waiting == false) ? this->handle_msg() : (void)0);

    handle_input();
    memset(this->buffer, 0x0, sizeof(this->buffer));
}

/**
 * send a message to the Client, telling it to start the game.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "12" + the id of the entity to work.
 */
void Lobby::sendLobbyJoin(int id, std::map<int, int> playersId)
{
    std::string data = "12 ";
    for (const auto& pair : playersId) {
        data += std::to_string(pair.first) + " " + std::to_string(pair.second) + " ";
    }
    sending(data);
}

/**
 * send a message to the Client, telling it to send the position of the entity.
 *
 * @param id The id of the entity.
 * @param x The x position of the entity.
 * @param y The y position of the entity.
 *
 * @attention This function has to send "20" + the id of the entity + the x position of the entity + the y position of the entity to work.
 */
void Lobby::sendPos(int id, float x, float y)
{
    sending("20 " + std::to_string(id) + " " + std::to_string(x) + " " + std::to_string(y));
}

void Lobby::sendPositions(std::map<int, std::vector<int>> msg)
{
    std::string data = "20 ";
    for (auto [id, pos] : msg) {
        data += std::to_string(id) + " " + std::to_string(pos[0]) + " " + std::to_string(pos[1]) + " ";
    }
    sending(data);

}

/**
 * send a message to the Client, telling it to shoot a level 1 bullet.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "31" + the id of the entity to work.
 */
void Lobby::sendShootLevel1(int id) { sending("31 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to shoot a level 2 bullet.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "32" + the id of the entity to work.
 */
void Lobby::sendShootLevel2(int id) { sending("32 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to shoot a level 3 bullet.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "33" + the id of the entity to work.
 */
void Lobby::sendShootLevel3(int id) { sending("33 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to shoot a level 4 bullet.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "34" + the id of the entity to work.
 */
void Lobby::sendShootLevel4(int id) { sending("34 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to shoot a rocket
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "35" + the id of the entity to work.
 */
void Lobby::sendShootRocket(int id) { sending("35 " + std::to_string(id)); }
/**
 * send a message to the Client, telling it to send the position of the collider.
 *
 * @param id The id of the entity.
 * @param w The width position of the collider.
 * @param h The height position of the collider.
 *
 * @attention This function has to send "36" + the id of the entity + the w position of the entity + the h position of the entity to work.
 */
void Lobby::sendCollider(int id, int w, int h) {
    sending("36 " + std::to_string(id) + " " + std::to_string(w) + " " + std::to_string(h));
}

void Lobby::sendColliders(std::map<int, std::vector<int>> msg)
{
    std::string data = "36 ";
    for (auto [id, pos] : msg) {
        data += std::to_string(id) + " " + std::to_string(pos[0]) + " " + std::to_string(pos[1]) + " " + std::to_string(pos[2]) + " ";
    }
    sending(data);
}

void Lobby::sendHealthUpdate(std::map<int, std::vector<int>> msg) {
    std::string data = "37 ";
    for (auto [id, pos] : msg) {
        data += std::to_string(id) + " " + std::to_string(pos[0]) + " " + std::to_string(pos[1]) + " " + std::to_string(pos[2]) + " ";
    }
    sending(data);
}
/**
 * send a message to the Client, telling it to disconnect.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "40" + the id of the entity to work.
 */
void Lobby::sendPlayerDisconnect(int id) { sending("40 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to destruct an AI.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "41" + the id of the entity to work.
 */
void Lobby::sendAIDisconnect(int id) { sending("41 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to send an error.
 *
 * @param id The id of the entity.
 *
 * @attention This function has to send "50" + the id of the entity to work.
 */
void Lobby::sendError(int id) { sending("50 " + std::to_string(id)); }

/**
 * send a message to the Client, telling it to stop the game on a Loose.
 *
 * @attention This function has to send "68".
 */
void Lobby::sendLose() {
    std::string scoreFilePath;

    if (_launchedGameType == EcsGameType::INF)
        scoreFilePath = "src/Server/scores/infScore.txt";
    else
        scoreFilePath = "src/Server/scores/levelScore.txt";

    std::ifstream file(scoreFilePath);
    std::ofstream outFile;

    if (file.is_open()) {
        std::string bestScoreStr;
        std::getline(file, bestScoreStr);

        int bestScore = std::stoi(bestScoreStr);

        if (score > bestScore) {
            file.close();

            outFile.open(scoreFilePath, std::ios::trunc);
            if (outFile.is_open()) {
                outFile << score;
                outFile.close();
            } else
                throw Error("Can't open score file for writing");
        }

        sending("68 " + std::to_string(score) + " " + bestScoreStr);
    } else
        throw Error("Can't open score file");
}

/**
 * send a message to the Client, telling it to stop the game on a Win.
 *
 * @attention This function has to send "69".
 */
void Lobby::sendWin() {
    std::string scoreFilePath;

    if (_launchedGameType == EcsGameType::INF)
        scoreFilePath = "src/Server/scores/infScore.txt";
    else
        scoreFilePath = "src/Server/scores/levelScore.txt";

    std::ifstream file(scoreFilePath);
    std::ofstream outFile;

    if (file.is_open()) {
        std::string bestScoreStr;
        std::getline(file, bestScoreStr);

        int bestScore = std::stoi(bestScoreStr);

        if (score > bestScore) {
            file.close();

            outFile.open(scoreFilePath, std::ios::trunc);
            if (outFile.is_open()) {
                outFile << score;
                outFile.close();
            } else
                throw Error("Can't open score file for writing");
        }

        sending("69 " + std::to_string(score) + " " + bestScoreStr);
    } else
        throw Error("Can't open score file");
}

/**
 * send a message to the Client, telling it on what level all player are.
 *
 * @attention This function has to send "60" for infinite level, "61" for level 1, "62" for level 2, "63" for level 3 & "64" for boss level.
 */
void Lobby::sendLevel() {
    if (engine._systemAI->_gameType == EcsGameType::INF) {
        sending("60");
    } else {
        sending("6" + std::to_string(static_cast<int>(engine._systemAI->_gameType)));
    }
}

/**
 * send a message to the Client, telling it that the is close.
 *
 * @attention This function has to send "13".
 */
void Lobby::sendCloseLobby() {
    sending("13");
}

/**
 * send a message to the Client, telling the score.
 *
 * @attention This function has to send "70"  + the score.
 */
void Lobby::sendScoreUpdate() {
    sending("70 " + std::to_string(score));
}


bool Lobby::in_lobby(void)
{
    std::cout << "IN LOBBY --------------------------" << std::endl;
    while (start_game == false) {
        if (number_of_players == 1) {
            start_game = true;
            std::cout << "Starting game..." << std::endl;
        }
        listening();
    }
    if (!in_game())
        sendLose();
    if (closed == false) {
        waiting = true;
        std::cout << "wait reconnect" << std::endl;
        bool done = false;
        while(done == false) {
            listening();
            for (const auto& pair : _replayOrQuitPlayer) {
                if (pair.second == true) {
                    std::cout << "at least one want replay" << std::endl;
                    return true;
                }
            }
            if (computerIds.empty() == true && spectatorPlayers.empty() == true)
                done = true;
        }
        std::cout << "no replay" << std::endl;
    }
    return false;
}

void Lobby::sleepFor(float time)
{
    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();
    float accumulatedTime = 0.0f;

    while (accumulatedTime < time) {
        elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();
        accumulatedTime += deltaTime;
    }
}

void Lobby::updateScoresAndSend()
{
    timeScoreUpdater += 1;

    if (timeScoreUpdater == fps) {
        if (engine._systemAI->_gameType == EcsGameType::INF)
            score += (1 + engine._systemAI->_gameType);
        else
            score += engine._systemAI->_gameType;
        sendScoreUpdate();
        timeScoreUpdater = 0;
    }
}

void Lobby::updateEntitiesMessages()
{
    for (auto [id, entity] : engine.gameObjects->getEntities()) {
        if (entity->hasComponent<Collider>() && entity->hasComponent<TypeEntity>() && entity->id > lastEntityId) {
            msgCollider[id] = {(int)entity->getComponent<Collider>().width, (int)entity->getComponent<Collider>().height, entity->getComponent<TypeEntity>().t};
            lastEntityId = entity->id;
        }

        if (entity->hasComponent<Input>() && entity->getComponent<Input>().isUpdated) {
            msg[id] = {(int)entity->getComponent<Position>().x, (int)entity->getComponent<Position>().y};
        }
    }
    //optimisation
    for (auto entity : engine.gameObjects->entitiesDamaged) {
        if (computerIds.find(entity->id) != computerIds.end()) {
            msgHealth[entity->id] = {entity->getComponent<Health>().health, entity->getComponent<Health>().maxHealth, entity->getComponent<TypeEntity>().t};
        }
    }
}

void Lobby::sendUpdatedEntities()
{
    if (msg.size() > 0)
        sendPositions(msg);
    if (msgCollider.size() > 0)
        sendColliders(msgCollider);
    if (msgHealth.size() > 0)
        sendHealthUpdate(msgHealth);
}

void Lobby::processDisconnectedEntities()
{
    for (auto entity : engine.gameObjects->entitiesToDestroy) {
        sendAIDisconnect(entity->id);
        if (entity.get()->getComponent<TypeEntity>().t == enemy) {
            engine._systemAI->nbAidead++;
            score += 5;
        }
        if (entity.get()->getComponent<TypeEntity>().t == boss) {
            engine._systemAI->bossIsDead = true;
            score += 100;
        }
        if (computerIds.find(entity->id) != computerIds.end()) {
            std::cout << "Player " << entity->id << " disconnected" << std::endl;
            sendPlayerDisconnect(entity->id);
            score -= 20;
            if (score < 0)
                score = 0;
        } else {
            if (entity.get()->getComponent<TypeEntity>().t == enemy) {
                engine._systemAI->nbAidead++;
                if (entity->deathReason == EntityDeathReason::Killed)
                    score += 5;
            }
            if (entity.get()->getComponent<TypeEntity>().t == boss) {
                engine._systemAI->bossIsDead = true;
                score += 100;
            }

        }
    }
}

void Lobby::handleLevelChange()
{
    if (engine._systemAI->_gameType != EcsGameType::INF
    && ((engine._systemAI->_gameType != EcsGameType::BOSS
    || (engine._systemAI->bossIsSpawned && engine._systemAI->bossIsDead))
    && engine._systemAI->nbAidead >= engine._systemAI->maxAI)) {
        std::cout << "changement de lvl" << std::endl;
        engine._systemAI->update(engine.gameObjects, float(0.0f));
        auto result = engine.restart(start_game, lastEntityId);
        if (result == "WIN") {
            sendWin();
            ret = true;
        } else
            sending(result);
    }
}

void Lobby::clearMsgs()
{
    msg.clear();
    msgCollider.clear();
    msgHealth.clear();
}

bool Lobby::in_game(void)
{
    std::cout << "IN GAME --------------------------" << std::endl;
    engine.start(_launchedGameType);
    sendLevel();

    while (start_game) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        listening();

        if (timeSinceLastUpdate > timePerFrame) {
            updateScoresAndSend();
            engine.update(deltaTime.asMicroseconds());
            updateEntitiesMessages();

            sendUpdatedEntities();
            processDisconnectedEntities();

            timeSinceLastUpdate = sf::Time::Zero;
            clearMsgs();
        }
        engine.clean();

        handleLevelChange();
    }
    return ret;
}
