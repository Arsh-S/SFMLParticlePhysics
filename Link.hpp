//
// Created by Arsh Singh on 1/1/25.
//

#ifndef LINK_H
#define LINK_H
#include "Particle.hpp"

struct Link {
    Particle &p1;
    Particle &p2;
    float target_distance;

    Link (Particle &p1, Particle &p2, float target_distance) : p1(p1), p2(p2), target_distance(target_distance) {}

    void apply() {

    }

};

#endif //LINK_H
