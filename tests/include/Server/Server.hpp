/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Server.hpp
*/

#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory.h>

#include <Server/Lobby.hpp>

class Server {
private:
    CtrlC _ctrlC;
    char buffer[1024];
    unsigned short port;
    sf::IpAddress sender;
    sf::UdpSocket socket;
    std::size_t received;
    std::string text = "Hello world";

    // *if multithread
    // std::map<int, Lobby> lobbys;

public:
    /****** builders ******/
    Server(void);
    ~Server(void);

    /****** methods ******/
    int listener(void);
    void send_msg(std::string);

    /****** threading methods ******/
    void loop(void) noexcept;
    void run(void);

    /****** getters ******/

    /****** setters ******/
};
