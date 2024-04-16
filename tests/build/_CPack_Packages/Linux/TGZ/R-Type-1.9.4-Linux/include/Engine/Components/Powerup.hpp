/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Powerup
*/

#ifndef POWERUP_HPP_
    #define POWERUP_HPP_
    #include <Engine/Components/IComponent.hpp>

    enum Type {
        NONE,
        HEALTH,
        SPEED,
        DAMAGE,
        DOUBLESHOOT,
        ROCKETSOOT
    };
    class Powerup : public virtual IComponent{
        public:
            Powerup(Type t, int value) : t(t), value(value) {};
            ~Powerup() = default;

            Type t = NONE;
            int value = 0;
        protected:
        private:
    };

#endif /* !POWERUP_HPP_ */
