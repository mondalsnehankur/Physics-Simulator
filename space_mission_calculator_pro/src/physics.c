#include "space.h"
#include <math.h>

double surface_gravity(double mass_kg, double radius_m) {
    if (mass_kg <= 0.0 || radius_m <= 0.0) return NAN;
    return G * mass_kg / (radius_m * radius_m);
}

double escape_velocity(double mass_kg, double radius_m) {
    if (mass_kg <= 0.0 || radius_m <= 0.0) return NAN;
    return sqrt(2.0 * G * mass_kg / radius_m);
}

double weight_newtons(double object_mass_kg, double gravity_m_s2) {
    if (object_mass_kg < 0.0 || gravity_m_s2 < 0.0) return NAN;
    return object_mass_kg * gravity_m_s2;
}

double circular_orbital_velocity(double central_mass_kg, double orbital_radius_m) {
    if (central_mass_kg <= 0.0 || orbital_radius_m <= 0.0) return NAN;
    return sqrt(G * central_mass_kg / orbital_radius_m);
}

double circular_orbital_period_days(double central_mass_kg, double orbital_radius_m) {
    if (central_mass_kg <= 0.0 || orbital_radius_m <= 0.0) return NAN;
    return (2.0 * PI * sqrt(pow(orbital_radius_m, 3.0) /
           (G * central_mass_kg))) / SECONDS_PER_DAY;
}

double approximate_travel_time_days(double distance_km, double speed_km_s) {
    if (distance_km < 0.0 || speed_km_s <= 0.0) return NAN;
    return (distance_km / speed_km_s) / SECONDS_PER_DAY;
}
