#include "space.h"

static const CelestialBody bodies[] = {
    {"Mercury", 3.3011e23, 2.4397e6, 57900000.0, 87.97, 0, ORBIT_SUN, "Smallest planet; no natural moons."},
    {"Venus", 4.8675e24, 6.0518e6, 108200000.0, 224.70, 0, ORBIT_SUN, "Dense atmosphere; surface conditions are extreme."},
    {"Earth", 5.9722e24, 6.3710e6, 149600000.0, 365.25, 1, ORBIT_SUN, "Reference planet for many comparisons."},
    {"Moon", 7.342e22, 1.7374e6, 149600000.0, 27.32, 0, ORBIT_EARTH, "Orbital period is around Earth; heliocentric formulas are not applied to it."},
    {"Mars", 6.4171e23, 3.3895e6, 227900000.0, 687.0, 2, ORBIT_SUN, "Often called the Red Planet."},
    {"Jupiter", 1.8982e27, 6.9911e7, 778500000.0, 4332.59, 95, ORBIT_SUN, "Largest planet in the Solar System."},
    {"Saturn", 5.6834e26, 5.8232e7, 1434000000.0, 10759.22, 146, ORBIT_SUN, "Known for its extensive ring system."},
    {"Uranus", 8.6810e25, 2.5362e7, 2871000000.0, 30688.5, 28, ORBIT_SUN, "An ice giant with an extreme axial tilt."},
    {"Neptune", 1.02413e26, 2.4622e7, 4495100000.0, 60182.0, 16, ORBIT_SUN, "A distant ice giant."},
    {"Sun", 1.98847e30, 6.9634e8, 0.0, 0.0, 0, ORBIT_NONE, "Star at the centre of the Solar System."}
};

const CelestialBody *get_bodies(size_t *count) {
    if (count) *count = sizeof(bodies) / sizeof(bodies[0]);
    return bodies;
}
