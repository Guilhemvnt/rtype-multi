/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** main.cpp
*/

#include <Error/Error.hpp>
#include <Server/Lobby.hpp>
#include <Engine/Engine.hpp>
#include <Server/Server.hpp>

int start_server(void)
{
    sf::Clock clock;

    std::unique_ptr<Server> server = std::make_unique<Server>();

    while (1) {
        int resp = server.get()->listener();
        if (resp == 1) break;
    }

    return 0;
}

int start_engine() {
    sf::Clock clock;

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->start(EcsGameType::INF);

    float timeElapsed = 0;

    bool isRunning = true;
    while (isRunning) {
        float deltaTime = clock.restart().asSeconds();
        timeElapsed += deltaTime;

        if (timeElapsed >= 1.0f) {
            engine->update(timeElapsed);
            timeElapsed = 0;
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    (void)argv;

    //! remove this when merge on main
    if (argc == 2 && std::string(argv[1]) == "engine")
        return start_engine();
    //! remove this when merge on main

    if (argc != 1) throw Error("Usage: ./server");

    return start_server();
}
