/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
    #define ENTITYFACTORY_HPP_
    #include <memory>
    #include <fstream>
    #include <iostream>
    #include <JsonParser/JsonParser.hpp>
    #include <Engine/Entities/Entity.hpp>
    #include <Engine/Components/Input.hpp>
    #include <Engine/Components/Health.hpp>
    #include <Engine/Components/Weapon.hpp>
    #include <Engine/Components/Position.hpp>
    #include <Engine/Components/Collider.hpp>
    #include <Engine/Components/TypeEntity.hpp>
    #include <Engine/Components/Powerup.hpp>

    class EntityFactory {
        public:
            EntityFactory(void);
            ~EntityFactory(void);

            Entity &createEntity(std::string);

        private:
            JsonParser parser;
    };

#endif /* !ENTITYFACTORY_HPP_ */
