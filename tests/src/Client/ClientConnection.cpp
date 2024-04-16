/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ClientConnection
*/

#include <Client/ClientConnection.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <Error/Error.hpp>

/**
 * Constructor of the ClientConnection class.
 *
 * @param serverIp The ip of the server.
 * @param serverPort The port of the server.
 *
 * @return The id of the entity.
 */
ClientConnection::ClientConnection(sf::IpAddress serverIp, unsigned short serverPort)
: _serverIp(serverIp), _port(serverPort)
{
    setClientPort();
}

/**
 * Destructor of the ClientConnection class.
 */
ClientConnection::~ClientConnection() { }

/**
 * send a message to the server.
 *
 * @param msg The message to send.
 */
void ClientConnection::sendMessage(const std::string msg)
{
    sf::Packet sendPacket;
    sendPacket << msg;
    if (_socket.send(sendPacket, _serverIp, _port) != sf::Socket::Status::Done) {
        // Disconnect the player if the server is unreachable
        throw Error("Failed to send message to server.");
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::cout << "Message sent to " << (_port == 4444 ? "lobby: " : "server: ") << msg <<" at "
                << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << std::endl;
}

/**
 * The function `isValidIP` checks if a given string is a valid IP address using regular expressions.
 *
 * @param ip The `ip` parameter is a `std::string` that represents an IP address.
 *
 * @return a boolean value.
 */
bool ClientConnection::isValidIP(const std::string& ip) {
    // Expression régulière pour une adresse IP
    const std::regex ipRegex("\\b(?:10(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])){3}|192\\.168(?:\\.(?:[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])){2}|127\\.0\\.0\\.1)\\b");

    return std::regex_match(ip, ipRegex);
}

/**
 * send a message to the server, telling it to create an infinte level.
 *
 * @attention This function has to send "10" to work.
 */
void ClientConnection::sendLobbyInfCreation() { sendMessage("10"); }

/**
 * send a message to the server, telling it to create a level.
 *
 * @attention This function has to send "11" to work.
 */
void ClientConnection::sendLobbyLvlCreation() { sendMessage("11"); }

/**
 * send a message to the server, telling it to join a lobby.
 *
 * @attention This function has to send "12" to work.
 */
void ClientConnection::sendLobbyJoin() { sendMessage("12"); }

/**
 * send a message to the server, telling it to move up.
 *
 * @attention This function has to send "20" to work.
 */
void ClientConnection::sendMoveUp() { sendMessage("20"); }

/**
 * send a message to the server, telling it to move down.
 *
 * @attention This function has to send "21" to work.
 */
void ClientConnection::sendMoveDown() { sendMessage("21"); }

/**
 * send a message to the server, telling it to move right.
 *
 * @attention This function has to send "22" to work.
 */
void ClientConnection::sendMoveRight() { sendMessage("22"); }

/**
 * send a message to the server, telling it to move left.
 *
 * @attention This function has to send "23" to work.
 */
void ClientConnection::sendMoveLeft() { sendMessage("23"); }

/**
 * send a message to the server, telling it to cancel the move on the x axis.
 *
 * @attention This function has to send "24" to work.
 */
void ClientConnection::sendCancelMoveX() { sendMessage("24"); }

/**
 * send a message to the server, telling it to cancel the move on the y axis.
 *
 * @attention This function has to send "25" to work.
 */
void ClientConnection::sendCancelMoveY() { sendMessage("25"); }

/**
 * send a message to the server, telling it to shoot a level 0 bullet.
 *
 * @attention This function has to send "30" to work.
 */
void ClientConnection::sendShootLevel0() { sendMessage("30"); }

/**
 * send a message to the server, telling it to shoot a level 1 bullet.
 *
 * @attention This function has to send "31" to work.
 */
void ClientConnection::sendShootLevel1() { sendMessage("31"); }

/**
 * send a message to the server, telling it to shoot a level 2 bullet.
 *
 * @attention This function has to send "32" to work.
 */
void ClientConnection::sendShootLevel2() { sendMessage("32"); }

/**
 * send a message to the server, telling it to shoot a level 3 bullet.
 *
 * @attention This function has to send "33" to work.
 */
void ClientConnection::sendShootLevel3() { sendMessage("33"); }

/**
 * send a message to the server, telling it to shoot a level 4 bullet.
 *
 * @attention This function has to send "34" to work.
 */
void ClientConnection::sendShootLevel4() { sendMessage("34"); }

/**
 * send a message to the server, telling it to cancel the shoot.
 *
 * @attention This function has to send "35" to work.
 */
void ClientConnection::sendCancelShoot() { sendMessage("35"); }

/**
 * send a message to the server, telling it to shoot a rocket.
 *
 * @attention This function has to send "36" to work.
 */
void ClientConnection::sendShootRocket() { sendMessage("36"); }

/**
 * send a message to the server, telling it to disconnect the player.
 *
 * @attention This function has to send "40" to work.
 */
void ClientConnection::sendPlayerDisconnect() { sendMessage("40"); }

/**
 * send a message to the server, telling it to logout the player.
 *
 * @attention This function has to send "42" to work.
 */
void ClientConnection::sendLogout() { sendMessage("42"); }

/**
 * send a message to the server, telling it to retry the connection.
 *
 * @attention This function has to send "67" to work.
 */
void ClientConnection::sendRetry() { sendMessage("67"); }

/**
 * handle lobbys management in their creation and joining.
 *
 * @param msg The message received from the server.
 */
int ClientConnection::lobbyManagement(std::string msg)
{
    if (msg == "10") {
        std::cout << "Lobby Inf created" << std::endl;
        _port = 4444;
    } else if (msg.compare(0, 2, "11") == 0) {
        std::cout << "Lobby Lvl created" << std::endl;
        _port = 4444;
    } else if (msg.compare(0, 2, "12") == 0) {
        std::cout << "Lobby joined" << std::endl;
        _myID = msg.substr(2);
        _state = ClientState::Playing;
    } else {
        throw Error("Error in Lobby");
        return 84;
    }
    return 0;
}

/**
 * handle the movement management in the game.
 *
 * @param msg The message received from the server.
 */
int ClientConnection::moveManagement(std::string msg)
{
    if (msg.compare(0, 2, "20") == 0 && msg.substr(2) == _myID) {
        std::cout << "Moved up" << std::endl;
    } else if (msg.compare(0, 2, "21") == 0 && msg.substr(2) == _myID) {
        std::cout << "Moved down" << std::endl;
    } else if (msg.compare(0, 2, "22") == 0 && msg.substr(2) == _myID) {
        std::cout << "Moved left" << std::endl;
    } else if (msg.compare(0, 2, "23") == 0 && msg.substr(2) == _myID) {
        std::cout << "Moved right" << std::endl;
    } else {
        throw Error("Error in Move");
        return 84;
    }
    return 0;
}

/**
 * handle the shoot management in the game.
 *
 * @param msg The message received from the server.
 * @param id The id of the entity.
 */
int ClientConnection::shootManagement(std::string msg, std::string id)
{
    if (msg.compare(0, 2, "30") == 0 && msg.substr(2) == id) {
        std::cout << "shooted level 0" << std::endl;
    } else if (msg.compare(0, 2, "31") == 0 && msg.substr(2) == id) {
        std::cout << "shooted level 1" << std::endl;
    } else if (msg.compare(0, 2, "32") == 0 && msg.substr(2) == id) {
        std::cout << "shooted level 2" << std::endl;
    } else if (msg.compare(0, 2, "33") == 0 && msg.substr(2) == id) {
        std::cout << "shooted level 3" << std::endl;
    } else if (msg.compare(0, 2, "34") == 0 && msg.substr(2) == id) {
        std::cout << "shooted level 4" << std::endl;
    } else {
        throw Error("Error in Shoot");
        return 84;
    }
    return 0;
}

/**
 * handle the disconnection from the players in the game.
 *
 * @param msg The message received from the server.
 */
int ClientConnection::disconnectManagement(std::string msg)
{
    if (msg.compare(0, 2, "40") == 0 && msg.substr(2) == _myID) {
        std::cerr << "Disconected" << std::endl;
        std::cout << "Please rejoin the lobby" << std::endl;
        _state = ClientState::Waiting;
    } else {
        throw Error("Error in Disconnect");
        return 84;
    }
    return 0;
}

/**
 * infinte loop to receive messages from the server.
 */
std::string ClientConnection::listener() {
    _socket.setBlocking(false);

    sf::IpAddress senderIp;
    unsigned short senderPort;
    sf::Packet receivePacket;
    std::string msg;
    sf::Socket::Status status = _socket.receive(receivePacket, senderIp, senderPort);

    if (status == sf::Socket::Status::Done) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::string receivedData;
        receivePacket >> receivedData;
        memset(_buffer, 0x0, sizeof(_buffer));
        if (receivedData.compare(0, 2, "12") == 0 && _myID.empty())
            _myID = receivedData.substr(3);
        return receivedData;
    } else if (status == sf::Socket::Status::NotReady) {
        return "";
    } else {
        std::cerr << "Failed to receive message from server. Error code: " << status << std::endl;
        return "";
    }
}

/**
 * The function sets the server IP address for a client connection if the provided IP address is valid.
 *
 * @param serverIp The server IP address that needs to be set.
 */
void ClientConnection::setServerIp(const std::string& serverIp)
{
    if (isValidIP(serverIp)) {
        this->_serverIp = serverIp;
    }
}

/**
 * setter for the variable of the port of the server.
 */
void ClientConnection::setServerPort(unsigned short serverPort)
{
    this->_port = serverPort;
}

/**
 * getter for the variable of the ip of the server.
 */
sf::IpAddress ClientConnection::getServerIp() { return this->_serverIp; }

/**
 * getter for the variable of the port of the server.
 */
unsigned short ClientConnection::getServerPort() { return this->_port; }

/**
 * setter for the variable of the port of the client.
 */
unsigned short ClientConnection::setClientPort()
{
    unsigned short port = 9000;
    while (_socket.bind(port) != sf::Socket::Status::Done) {
        port++;
    }
    std::cout << "Client port: " << port << std::endl;
    return port;
}

