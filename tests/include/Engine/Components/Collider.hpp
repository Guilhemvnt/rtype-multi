/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Collider
*/

#ifndef COLLIDER_HPP_
    #define COLLIDER_HPP_
    #include <Engine/Components/IComponent.hpp>
    #include <string>

class Collider : public IComponent {
public:
    float width;
    float height;
    int layer;

    bool colliding = false;

    Collider(float width, float height, int layer)
        : width(width)
        , height(height)
        , layer(layer) {};
    ~Collider() = default;
};
inline std::ostream& operator<<(std::ostream& out, const Collider* collider)
{
    out << "Collider: " << collider->width << ", " << collider->height << ' '
        << collider->layer << std::endl;
    return out;
}
inline std::string getColliderString(const Collider* collider)
{
    std::string str = "Collider: " + std::to_string(collider->width) + ", " + std::to_string(collider->height) + ' ' + std::to_string(collider->layer);
    return str;
}

#endif /* !COLLIDER_HPP_ */
