/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Server.hpp
*/

#pragma once

#include <map>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <cstring>
#include <iostream>
#include <Engine/Engine.hpp>
#include <iomanip>
#include <chrono>

#include <CtrlC/CtrlC.hpp>

#include <SFML/Network.hpp>

class Lobby {
private:
    JsonParser parser;
    CtrlC _ctrlC;

    char buffer[1024];
    unsigned short port;
    sf::IpAddress sender;
    sf::UdpSocket socket;
    std::size_t received;
    bool start_game = false;
    int number_of_players = 0;
    std::string text = "Hello world";
    std::map<int, std::pair<sf::IpAddress, unsigned short>> computerIds;
    std::map<int, std::pair<sf::IpAddress, unsigned short>> spectatorPlayers;
    std::map<std::pair<sf::IpAddress, unsigned short>, bool> _replayOrQuitPlayer;
    Engine engine;
    bool waiting = false;
    bool closed = false;

    //*clock d'update ECS
    sf::Clock clock = sf::Clock();
    float fps;
    sf::Time timePerFrame;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    EcsGameType _launchedGameType;

    std::map<int, int> PlayersID = {
        {0, -1},
        {1, -1},
        {2, -1},
        {3, -1},
    };

    bool IsUp = false;
    bool Stopping = false;
    int lastEntityId = 0;

    int score;
    int timeScoreUpdater = 0;

    public:
        bool ret = false;
        std::map<int, std::vector<int>> msg;
        std::map<int, std::vector<int>> msgCollider;
        std::map<int, std::vector<int>> msgHealth;

        /****** builders ******/
        ~Lobby(void) {}
        Lobby(unsigned short port, EcsGameType);

        /****** methods ******/

        void sendLobbyJoin(int id, std::map<int, int>);

        void sendPos(int id, float x, float y);

        void sendShootLevel0(int id);

        void sendShootLevel1(int id);

        void sendShootLevel2(int id);

        void sendShootLevel3(int id);

        void sendShootLevel4(int id);

        void sendShootRocket(int id);

        void sendPositions(std::map<int, std::vector<int>> msg);

        void sendCollider(int id, int w, int h);
        void sendColliders(std::map<int, std::vector<int>> msg);
        void sendHealthUpdate(std::map<int, std::vector<int>> msg);

        void sendPlayerDisconnect(int id);
        void sendAIDisconnect(int id);

        void sendLose();
        void sendWin();

        void sendLevel();

        void sendCloseLobby();

        void sendScoreUpdate();

        void sendError(int id);

        /****** getters ******/

        /****** handling ******/
        void handle_msg(void);

        /****** connections ******/
        void setPlayerID(int);
        void new_connection(void);
        void delete_connection(void);

        /****** general ******/
        bool in_lobby();
        bool in_game();
        void listening(void);
        void sending(std::string);

        void handle_input(void);
        void sleepFor(float time);

        void moveIntoToReplayOrQuit(bool replay);

        void decoPlayer();

        void updateScoresAndSend();
        void updateEntitiesMessages();
        void sendUpdatedEntities();

        void processDisconnectedEntities();
        void handleLevelChange();
        void clearMsgs();
};
