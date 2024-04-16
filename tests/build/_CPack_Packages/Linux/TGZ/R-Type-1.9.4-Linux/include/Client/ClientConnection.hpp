/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ClientConnection
*/

#ifndef CLIENTCONNECTION_HPP_
#define CLIENTCONNECTION_HPP_

#include <string>
#include <iostream>
#include <memory.h>
#include <regex>

#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>

class ClientConnection {
public:

    enum class ClientState {
        Waiting,
        Playing,
    };

    ClientConnection(sf::IpAddress serverIp, unsigned short serverPort);
    ~ClientConnection();

    std::string listener();

    bool isValidIP(const std::string& ip);

    void sendLobbyInfCreation();
    void sendLobbyLvlCreation();
    void sendLobbyJoin();

    void sendMoveUp();
    void sendMoveDown();
    void sendMoveRight();
    void sendMoveLeft();
    void sendCancelMoveX();
    void sendCancelMoveY();

    void sendShootLevel0();
    void sendShootLevel1();
    void sendShootLevel2();
    void sendShootLevel3();
    void sendShootLevel4();
    void sendCancelShoot();
    void sendShootRocket();


    void sendPlayerDisconnect();
    void sendLogout();
    void sendRetry();

    void setServerIp(const std::string& serverIP);
    void setServerPort(unsigned short serverPort);

    sf::IpAddress getServerIp();
    unsigned short getServerPort();

    unsigned short setClientPort();

    void run();
    void in_lobby();
    void waitingRoom();

    int lobbyManagement(std::string msg);
    static int shootManagement(std::string msg, std::string id);
    int moveManagement(std::string msg);
    int disconnectManagement(std::string msg);

    ClientState _state = ClientState::Waiting;
    unsigned short _port;
    std::string _myID;
private:
    sf::IpAddress _serverIp;
    void sendMessage(const std::string msg);

    sf::UdpSocket _socket;
    char _buffer[1024];
    std::size_t _received;

protected:
};

#endif /* !CLIENTCONNECTION_HPP_ */
