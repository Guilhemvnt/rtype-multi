/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** EcsGameType
*/

#pragma once

#include <iostream>
#include <Error/Error.hpp>

enum class EcsGameType {
    INF,
    LVL1,
    LVL2,
    LVL3,
    BOSS,
    WIN,
    LOSE
};

inline std::ostream& operator<<(std::ostream& os, const EcsGameType& gameType) {
    switch (gameType) {
        case EcsGameType::INF:
            os << "INF";
            break;
        case EcsGameType::LVL1:
            os << "LVL1";
            break;
        case EcsGameType::LVL2:
            os << "LVL2";
            break;
        case EcsGameType::LVL3:
            os << "LVL3";
            break;
        case EcsGameType::BOSS:
            os << "BOSS";
            break;
        case EcsGameType::WIN:
            os << "WIN";
            break;
        case EcsGameType::LOSE:
            os << "LOSE";
            break;
        default:
            throw Error("Invalid game type");
    }
    return os;
}

inline EcsGameType operator++(EcsGameType& gameType, int) {
    switch (gameType) {
        case EcsGameType::WIN:
            gameType = EcsGameType::WIN;
            break;
        case EcsGameType::LOSE:
            gameType = EcsGameType::LOSE;
            break;
        case EcsGameType::INF:
            gameType = EcsGameType::INF;
            break;
        case EcsGameType::LVL1:
            gameType = EcsGameType::LVL2;
            break;
        case EcsGameType::LVL2:
            gameType = EcsGameType::LVL3;
            break;
        case EcsGameType::LVL3:
            gameType = EcsGameType::BOSS;
            break;
        case EcsGameType::BOSS: //? to change if more lvl is needed
            gameType = EcsGameType::WIN;
            break;
        default:
            throw Error("Invalid game type");
    }
    return gameType;
}

inline int operator+(const EcsGameType& gameType, int num) {
    return static_cast<int>(static_cast<int>(gameType) + num);
}

inline int operator+(int num, const EcsGameType& gameType) {
    return static_cast<int>(static_cast<int>(gameType) + num);
}

inline int& operator+=(int& num, const EcsGameType& gameType) {
    num += static_cast<int>(gameType);
    return num;
}
