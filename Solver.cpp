#include "Solver.h"

void Solver::addParticle(const Particle &particle) {
    particles.push_back(particle);
}

void Solver::update(const float dt, const int substepCount) {
    const float substepTime = dt / static_cast<float>(substepCount);
    for (int i = 0; i < substepCount; ++i) {
        applyGravity();
        applyConstraint();
        solveCollisions();
        updatePositions(substepTime);
    }
}

void Solver::solveCollisions() {
    for (std::size_t i = 0; i < particles.size(); ++i) {
        for (std::size_t j = i + 1; j < particles.size(); ++j) {
            Particle &p1 = particles[i];
            Particle &p2 = particles[j];

            sf::Vector2f collisionAxis = p2.position - p1.position;
            float distanceSquared = collisionAxis.x * collisionAxis.x + collisionAxis.y * collisionAxis.y;
            float radiusSum = p1.radius + p2.radius;

            if (distanceSquared < radiusSum * radiusSum) {
                float distance = std::sqrt(distanceSquared);
                if (distance == 0.0f) {
                    collisionAxis = {1.0f, 0.0f};
                    distance = radiusSum;
                } else {
                    collisionAxis /= distance;
                }

                float overlap = radiusSum - distance;
                p1.position -= 0.5f * overlap * collisionAxis;
                p2.position += 0.5f * overlap * collisionAxis;

                sf::Vector2f p1Velocity = p1.position - p1.oldPosition;
                sf::Vector2f p2Velocity = p2.position - p2.oldPosition;

                float p1Dot = p1Velocity.x * collisionAxis.x + p1Velocity.y * collisionAxis.y;
                float p2Dot = p2Velocity.x * collisionAxis.x + p2Velocity.y * collisionAxis.y;

                if (p2Dot - p1Dot > 0) {
                    continue;
                }

                float velocityDifference = p2Dot - p1Dot;
                sf::Vector2f impulse = velocityDifference * collisionAxis;

                p1.oldPosition -= impulse * dampeningFactor;
                p2.oldPosition += impulse * dampeningFactor;
            }
        }
    }
}

void Solver::applyConstraint() {
    for (Particle &p: particles) {

        if (p.position.x - p.radius < boundingBox.position.x) {
            p.position.x = boundingBox.position.x + p.radius;
            p.oldPosition.x = p.position.x;
        } else if (p.position.x + p.radius > boundingBox.position.x + boundingBox.size.x) {
            p.position.x = boundingBox.position.x + boundingBox.size.x - p.radius;
            p.oldPosition.x = p.position.x;
        }

        if (p.position.y - p.radius < boundingBox.position.y) {
            p.position.y = boundingBox.position.y + p.radius;
            p.oldPosition.y = p.position.y;
        } else if (p.position.y + p.radius > boundingBox.position.y + boundingBox.size.y) {
            p.position.y = boundingBox.position.y + boundingBox.size.y - p.radius;
            p.oldPosition.y = p.position.y;
        }

    }
}

void Solver::updatePositions(const float dt) {
    for (Particle &p: particles) {
        p.updatePosition(dt);
    }
}

void Solver::applyGravity() {
    for (Particle &p: particles) {
        p.accelerate(gravity);
    }
}