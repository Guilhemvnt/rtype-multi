/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ObjectPool
*/

#ifndef OBJECTPOOL_HPP_
#define OBJECTPOOL_HPP_
#pragma once

#include <Graph/GameObject.hpp>

class ObjectPool {
public:
    std::shared_ptr<GameObject> getObject();
    void returnObject(std::shared_ptr<GameObject> object);

private:
    std::vector<std::shared_ptr<GameObject>> objectPool;
};

#endif /* !OBJECTPOOL_HPP_ */
