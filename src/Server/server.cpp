/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Server.cpp
*/

#include <Server/Lobby.hpp>
#include <Server/Server.hpp>

Server::Server(void)
{
    if (socket.bind(8888) != sf::Socket::Status::Done) {
        throw Error("Already a server running");
    }

    //* pour multi thread
    // this->_connection_threads.emplace_back([this]() { listener(); });

    std::cout << "Server is running" << std::endl;
    std::cout << "Local ip is " << sf::IpAddress::getLocalAddress() << std::endl;
}

Server::~Server(void)
{
    //* pour multi thread
    /*for (auto &thread : this->_connection_threads) {
        if (thread.joinable()) thread.join();
    }
    */
}

void Server::run()
{
    //* pour multi thread
    /*for (auto &thread : this->_connection_threads) {
        if (thread.joinable()) thread.join();
    }*/
}

int Server::listener(void)
{
    _ctrlC.checkCtrlCPressed();
    if (_ctrlC.ctrlCPressed == true) {
        std::cerr << "ctrl C catched" << std::endl;
        return 1;
    }

    int ret = 0;

    std::cout << "Listening..." << std::endl;
    sf::Packet packetReceive;
    if (socket.receive(packetReceive, this->sender, this->port) != sf::Socket::Status::Done) {
        std::cout << "Error receiving message in server" << std::endl;
        return ret;
    }

    std::string msg;
    packetReceive >> msg;

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "Received \"" << msg << "\" from " << this->sender << " on port " << this->port <<" at "
            << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << std::endl;

    if (msg == "10") {
        this->send_msg("10");
        std::unique_ptr<Lobby> lobby = std::make_unique<Lobby>(4444, EcsGameType::INF);
        if (!lobby.get()->in_lobby())
            ret = 1;
        lobby.reset();
    }
    if (msg == "11") {
        this->send_msg("11");
        std::unique_ptr<Lobby> lobby = std::make_unique<Lobby>(4444, EcsGameType::LVL1);
        if (!lobby.get()->in_lobby())
            ret = 1;
        lobby.reset();
    }
    if (msg == "12")
        this->send_msg("50");

    return ret;
}

void Server::send_msg(std::string msg)
{
    sf::Packet packetSend;
    packetSend << msg.c_str();
    if (socket.send(packetSend, this->sender, this->port) != sf::Socket::Status::Done) {
        std::cout << "Error sending message" << std::endl;
        return;
    }

    std::cout << "Message sent to client: " << msg << std::endl;
}
