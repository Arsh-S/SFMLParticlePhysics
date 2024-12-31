#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

struct Particle {
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f acceleration;
    float radius;

    Particle(sf::Vector2f pos, sf::Vector2f velocity, float rad);

    void updatePosition(float dt);
    void accelerate(sf::Vector2f acc);
};

#endif //PARTICLE_H
