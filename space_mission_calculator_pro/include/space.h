#ifndef SPACE_H
#define SPACE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

#define G 6.67430e-11
#define PI 3.14159265358979323846
#define SUN_MASS 1.98847e30
#define SECONDS_PER_DAY 86400.0
#define DAYS_PER_YEAR 365.25

typedef enum {
    ORBIT_SUN = 0,
    ORBIT_EARTH = 1,
    ORBIT_NONE = 2
} OrbitType;

typedef struct {
    char name[32];
    double mass_kg;
    double radius_m;
    double distance_from_sun_km;
    double orbital_period_days;
    int moons;
    OrbitType orbit_type;
    const char *notes;
} CelestialBody;

const CelestialBody *get_bodies(size_t *count);
double surface_gravity(double mass_kg, double radius_m);
double escape_velocity(double mass_kg, double radius_m);
double weight_newtons(double object_mass_kg, double gravity_m_s2);
double circular_orbital_velocity(double central_mass_kg, double orbital_radius_m);
double circular_orbital_period_days(double central_mass_kg, double orbital_radius_m);
double approximate_travel_time_days(double distance_km, double speed_km_s);
int export_body_report_csv(const char *path, const CelestialBody *bodies, size_t count);
void show_menu(void);
void pause_for_enter(void);
int read_int_range(const char *prompt, int min, int max, int *out);
int read_positive_double(const char *prompt, double *out);
void show_body_list(const CelestialBody *bodies, size_t count);
void show_body_details(const CelestialBody *body);
void run_self_tests(void);

#endif
