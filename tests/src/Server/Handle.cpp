/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Handle.cpp
*/

#include <Server/Lobby.hpp>

/****** handling function ******/

/**
 * The function `handle_msg` in the `Lobby` class handles incoming messages by
 * mapping them to corresponding member functions and executing them.
 *
 * @return In the given code, the return statement is used to exit the function
 * and return control to the calling function. The return statement does not have
 * a value specified, so it will not return any specific value.
 */
void Lobby::handle_msg(void)
{
    std::map<std::string, void (Lobby::*)(void)> map = {
        { "12", &Lobby::new_connection },
    };

    if (map.find(this->buffer) == map.end()) {
        //! clean this when merge on main
        // std::cout << "[ERROR]: " << this->buffer << " is not a valid option"
        //           << std::endl;
        // this->sending("50");
        //! clean this when merge on main
        return;
    }

    (this->*map[this->buffer])();

    map.clear();
}

/****** connections ******/

/**
 * The function `handle_input` processes input based on the received buffer and
 * updates the game state accordingly.
 *
 * @return The function does not have a return type, so it does not return
 * anything.
 */
void Lobby::handle_input(void)
{
    if (start_game) {
        int entityID = 0;
        for (auto [id, data] : computerIds) {
            if (data.first == this->sender && data.second == this->port) {
                entityID = id;
            }
        }
        if (entityID == 0) {
            return;
        }
        if (strcmp(this->buffer, "40") == 0 && waiting == false) {
            delete_connection();
        } else if (strcmp(this->buffer, "20") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().y = -1;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = true;
        } else if (strcmp(this->buffer, "21") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().y = 1;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = true;
        } else if (strcmp(this->buffer, "22") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().x = 1;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = true;
        } else if (strcmp(this->buffer, "23") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().x = -1;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = true;
        } else if (strcmp(this->buffer, "24") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().x = 0;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = false;
        } else if (strcmp(this->buffer, "25") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().y = 0;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().isUpdated = false;
        } else if (strcmp(this->buffer, "30") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = true;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().shootLevel = 0;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammo = engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().maxAmmo;
        } else if (strcmp(this->buffer, "31") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = true;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().shootLevel = 1;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammo = engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().maxAmmo;
        } else if (strcmp(this->buffer, "32") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = true;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().shootLevel = 2;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammo = engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().maxAmmo;
        } else if (strcmp(this->buffer, "33") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = true;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().shootLevel = 3;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammo = engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().maxAmmo;
        } else if (strcmp(this->buffer, "34") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = true;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().shootLevel = 4;
            engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammo = engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().maxAmmo;
        } else if (strcmp(this->buffer, "35") == 0 && engine.gameObjects->hasEntity(entityID)) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().shoot = false;
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().rocketShoot = false;
        } else if (strcmp(this->buffer, "36") == 0 && engine.gameObjects->hasEntity(entityID) && engine.gameObjects->getEntityById(entityID)->getComponent<Weapon>().ammoRocket > 0) {
            engine.gameObjects->getEntityById(entityID)->getComponent<Input>().rocketShoot = true;
        }
    }
    if (strcmp(this->buffer, "67") == 0 && this->waiting == true) {
        moveIntoToReplayOrQuit(true);
    } else if (strcmp(this->buffer, "40") == 0 && this->waiting == true) {
        moveIntoToReplayOrQuit(false);
    } else if (strcmp(this->buffer, "42") == 0) {
        decoPlayer();
    }
}

void Lobby::setPlayerID(int entityID)
{
    for (auto [id, data] : PlayersID) {
        if (data == -1) {
            PlayersID[id] = entityID;
            break;
        }
    }
}

/**
 * The function `new_connection` is called when a new player connects to the
 * lobby, and it performs various actions such as adding the player to the game
 * engine, sending lobby join information, and sending game object positions and
 * colliders if the game has already started.
 */
void Lobby::new_connection(void)
{
    if (number_of_players > 4 || spectatorPlayers.size() > 0) {
        std::cout << "[INFO]: lobby full." << std::endl;
        this->sending("51");
        return;
    }
    std::pair<sf::IpAddress, unsigned short> tmp(this->sender, this->port);
    this->number_of_players++;
    int entityID = engine.addPlayer();
    computerIds[entityID] = tmp;
    std::cout << "[INFO]: new player connected." << std::endl;
    setPlayerID(entityID);
    sending("90 " + std::to_string(entityID));
    this->sendLobbyJoin(entityID, PlayersID);
    if (start_game == true) {

        sendLevel();

        std::map<int, std::vector<int>> msg;
        std::map<int, std::vector<int>> msgCollider;

        for (auto [id, entity] : engine.gameObjects->getEntities()) {
            if (entity->hasComponent<Collider>())
                msgCollider[id] = {(int)entity->getComponent<Collider>().width, (int)entity->getComponent<Collider>().height, entity->getComponent<TypeEntity>().t};

            if (entity->hasComponent<Input>())
                msg[id] = {(int)entity->getComponent<Position>().x, (int)entity->getComponent<Position>().y};
        }
        for (auto [id, entity] : engine.gameObjects->getEntities()) {
            if (computerIds.find(entity->id) != computerIds.end()) {
                msgHealth[entity->id] = {entity->getComponent<Health>().health, entity->getComponent<Health>().maxHealth, entity->getComponent<TypeEntity>().t};
            }
        }

        if (msg.size() > 0)
            sendPositions(msg);
        if (msgCollider.size() > 0)
            sendColliders(msgCollider);
        if (msgHealth.size() > 0)
            sendHealthUpdate(msgHealth);
    }
}

/**
 * The function "delete_connection" removes a connection from a lobby and updates
 * the number of players accordingly.
 */
void Lobby::delete_connection(void)
{
    std::pair<sf::IpAddress, unsigned short> tmp(this->sender, this->port);
    std::cout << "[INFO] deleting connection." << this->sender << " " << this->port <<std::endl;

    auto it = computerIds.begin();
    for (; it != computerIds.end(); ++it) {
        if (it->second == tmp) {
            auto tmpSocket = computerIds.extract(it);
            spectatorPlayers.insert(std::move(tmpSocket));
            break;
        }
    }
    if (this->computerIds.size() == 0 && this->start_game == true) {
        std::cout << "[INFO] all player dead" << std::endl;
        this->start_game = false;
    }
}

/**
 * The function moves a player from the lobby to either the replay or quit list.
 *
 * @param replay The "replay" parameter is a boolean value that indicates whether
 * the player wants to move into a replay or quit the lobby. If "replay" is true,
 * it means the player wants to move into a replay. If "replay" is false, it means
 * the player wants to quit
 */
void Lobby::moveIntoToReplayOrQuit(bool replay) {
    std::pair<sf::IpAddress, unsigned short> tmp(this->sender, this->port);

    for (auto it = computerIds.begin(); it != computerIds.end(); ++it) {
        if (it->second == tmp) {
            _replayOrQuitPlayer[tmp] = replay;
            computerIds.erase(it);
            break;
        }
    }

    for (auto it = spectatorPlayers.begin(); it != spectatorPlayers.end(); ++it) {
        if (it->second == tmp) {
            _replayOrQuitPlayer[tmp] = replay;
            spectatorPlayers.erase(it);
            break;
        }
    }
}

/**
 * The `decoPlayer` function removes a player from the lobby and updates the
 * number of players, and if all players are disconnected and the game has
 * started, it sets the `start_game` flag to false.
 */
void Lobby::decoPlayer(void)
{
    std::pair<sf::IpAddress, unsigned short> tmp(this->sender, this->port);
    std::cout << "[INFO] player disconnect." << this->sender << " " << this->port <<std::endl;

    auto it = computerIds.begin();
    for (; it != computerIds.end(); ++it) {
        if (it->second == tmp) {
            this->number_of_players--;
            std::cout << "[INFO] nb player left " << number_of_players << std::endl;
            _replayOrQuitPlayer[tmp] = false;
            for (auto [id, entity] : PlayersID) {
                if (entity == it->first) {
                    PlayersID[id] = -1;
                    break;
                }
            }
            engine.gameObjects->destroyEntityById(it->first);
            sendPlayerDisconnect(it->first);
            computerIds.erase(it);
            break;
        }
    }
    it = spectatorPlayers.begin();
    for (; it != spectatorPlayers.end(); ++it) {
        if (it->second == tmp) {
            _replayOrQuitPlayer[tmp] = false;
            spectatorPlayers.erase(it);
            break;
        }
    }
    if (this->computerIds.size() == 0 && this->start_game == true) {
        std::cout << "[INFO] all player dead" << std::endl;
        this->start_game = false;
    }
}
