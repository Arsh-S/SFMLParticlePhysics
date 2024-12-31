// Made by Arsh Singh
// Inspiration from @PezzzasWork (https://www.youtube.com/watch?v=lS_qeBy3aQI&)

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <optional>

#include "Particle.h"
#include "Solver.h"
#include "Utils.h"

int main() {
    Solver solver;
    std::mt19937 rng(std::random_device{}());

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Basic Particle Physics System");
    window.setFramerateLimit(120);

    const sf::Font font("./Resources/Arial.ttf");

    sf::Text fpsText(font, "FPS");
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition({static_cast<float>(window.getSize().x) / 2.0f - 50.0f, 10.0f});

    sf::Text particleCountText(font, "Particles");
    particleCountText.setCharacterSize(20);
    particleCountText.setFillColor(sf::Color::White);
    particleCountText.setPosition({static_cast<float>(window.getSize().x) / 2.0f - 50.0f, 50.0f});

    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;
    float elapsedTime = 0.0f;

    const int targetParticleCount = 1000;
    int currentParticleCount = 0;
    float spawnInterval = 0.075f;
    float timeSinceLastSpawn = 0.0f;

    const int rainbowLoops = 3;

    float sprayAngle = 20.0f;
    float angleIncrement = 3.0f;
    bool sprayDirection = true; // True for left, false for right

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        if (isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        const float deltaTime = clock.restart().asSeconds();
        timeSinceLastSpawn += deltaTime;

        if (currentParticleCount < targetParticleCount && timeSinceLastSpawn >= spawnInterval) {
            float x = static_cast<float>(window.getSize().x) / 2.0f;
            float y = 120.0f;
            float radius = std::uniform_real_distribution(7.0f, 17.0f)(rng);

            float angleRad = sprayAngle * sf::priv::pi / 180.0f;

            sf::Vector2f velocity(std::cos(angleRad) * 1.0f, std::sin(angleRad) * 1.0f);

            float hue = (static_cast<float>(currentParticleCount) / targetParticleCount) * rainbowLoops * 360.0f;
            sf::Color color = hsvToRgb(fmod(hue, 360.0f), 0.7f, 1.0f);

            Particle particle({x, y}, velocity, radius);
            particle.shape.setFillColor(color);
            solver.addParticle(particle);

            currentParticleCount++;
            particleCountText.setString("Particles: " + std::to_string(currentParticleCount));
            timeSinceLastSpawn = 0.0f;

            sprayAngle += angleIncrement * (sprayDirection ? 1.0f : -1.0f);
            if (sprayAngle >= 180.0f-20.0f || sprayAngle <= 20.0f) {
                sprayDirection = !sprayDirection;
            }
        }

        const int substepCount = 8;
        solver.update(deltaTime, substepCount);

        elapsedTime += fpsClock.restart().asSeconds();
        frameCount++;
        if (elapsedTime >= 1.0f) {
            fpsText.setString("FPS: " + std::to_string(frameCount));
            frameCount = 0;
            elapsedTime = 0.0f;
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape boundingBox;
        boundingBox.setSize({solver.boundingBox.size.x, solver.boundingBox.size.y});
        boundingBox.setPosition(solver.boundingBox.position);
        boundingBox.setFillColor(sf::Color::Transparent);
        boundingBox.setOutlineColor(sf::Color::White);
        boundingBox.setOutlineThickness(1.0f);
        window.draw(boundingBox);

        for (Particle &particle: solver.particles) {
            window.draw(particle.shape);
        }

        window.draw(fpsText);
        window.draw(particleCountText);

        window.display();
    }
}
