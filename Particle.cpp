#include "Particle.h"

Particle::Particle(const sf::Vector2f pos, const sf::Vector2f velocity, const float rad)
    : position(pos), oldPosition(pos - velocity), radius(rad) {
    shape = sf::CircleShape(radius);
    shape.setOrigin({radius, radius});
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);
}

void Particle::updatePosition(const float dt) {
    const sf::Vector2f velocity = position - oldPosition;
    oldPosition = position;
    position = position + velocity + acceleration * dt * dt;
    acceleration = {};
    shape.setPosition(position);
}

void Particle::accelerate(const sf::Vector2f acc) {
    acceleration += acc;
}