#include "Utils.hpp"
#include <SFML/Graphics.hpp>

sf::Color hsvToRgb(const float hue, const float saturation, const float value) {
    const float c = value * saturation;
    const float x = c * static_cast<float>(1 - std::fabs(fmod(hue / 60.0f, 2) - 1));
    const float m = value - c;

    float r, g, b;
    if (hue < 60) {
        r = c; g = x; b = 0;
    } else if (hue < 120) {
        r = x; g = c; b = 0;
    } else if (hue < 180) {
        r = 0; g = c; b = x;
    } else if (hue < 240) {
        r = 0; g = x; b = c;
    } else if (hue < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    return {
        static_cast<uint8_t>((r + m) * 255),
        static_cast<uint8_t>((g + m) * 255),
        static_cast<uint8_t>((b + m) * 255)
    };
}