#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "Particle.h"

struct Solver {
    std::vector<Particle> particles;
    sf::Vector2f gravity = {0.0f, 500.0f};
    float dampeningFactor = 0.1f;
    sf::FloatRect boundingBox = {sf::Vector2f(100.0f, 100.0f), sf::Vector2f(800.0f, 800.0f)};

    void addParticle(const Particle &particle);
    void update(float dt, int substepCount);

private:
    void solveCollisions();
    void applyConstraint();
    void updatePositions(float dt);
    void applyGravity();
};

#endif //SOLVER_H
