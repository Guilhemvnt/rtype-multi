/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_
#include <Engine/Systems/ISystem.hpp>

class CollisionSystem : virtual public ISystem {
public:
    CollisionSystem();
    ~CollisionSystem();

    void update(std::shared_ptr<EntityManager>&, float deltaTime);

private:
    bool isCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity>  entity2, int entityID1, int entityID2);
    bool isDead(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity>  entity2);
    void setPowerUp(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity>  entity2);

};

#endif /* !COLLISIONSYSTEM_HPP_ */
