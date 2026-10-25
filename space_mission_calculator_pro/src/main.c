#include "space.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

static int choose_body(const CelestialBody *bodies, size_t count, const char *prompt, size_t *index) {
    int choice;
    show_body_list(bodies, count);
    if (!read_int_range(prompt, 1, (int)count, &choice)) return 0;
    *index = (size_t)(choice - 1);
    return 1;
}

static void print_velocity(const CelestialBody *b) {
    double value = escape_velocity(b->mass_kg, b->radius_m);
    printf("%s escape velocity: %.4f km/s\n", b->name, value / 1000.0);
}

static void print_gravity(const CelestialBody *b) {
    printf("%s surface gravity: %.4f m/s^2\n", b->name, surface_gravity(b->mass_kg, b->radius_m));
}

static void custom_body(void) {
    double mass, radius, g, ve;
    puts("\nCustom body calculator");
    if (!read_positive_double("Enter body mass in kg: ", &mass)) return;
    if (!read_positive_double("Enter body radius in metres: ", &radius)) return;
    g = surface_gravity(mass, radius);
    ve = escape_velocity(mass, radius);
    printf("\nResults for your custom body\n");
    printf("Surface gravity: %.5f m/s^2\n", g);
    printf("Escape velocity: %.5f km/s\n", ve / 1000.0);
}

static void compare_bodies(const CelestialBody *a, const CelestialBody *b) {
    printf("\n%-28s | %-18s | %-18s\n", "Property", a->name, b->name);
    puts("--------------------------------------------------------------------------");
    printf("%-28s | %18.5e | %18.5e\n", "Mass (kg)", a->mass_kg, b->mass_kg);
    printf("%-28s | %18.5e | %18.5e\n", "Radius (m)", a->radius_m, b->radius_m);
    printf("%-28s | %18.4f | %18.4f\n", "Surface gravity (m/s^2)",
           surface_gravity(a->mass_kg, a->radius_m), surface_gravity(b->mass_kg, b->radius_m));
    printf("%-28s | %18.4f | %18.4f\n", "Escape velocity (km/s)",
           escape_velocity(a->mass_kg, a->radius_m) / 1000.0,
           escape_velocity(b->mass_kg, b->radius_m) / 1000.0);
    printf("%-28s | %18.3f | %18.3f\n", "Distance from Sun (million km)",
           a->distance_from_sun_km / 1.0e6, b->distance_from_sun_km / 1.0e6);
    printf("%-28s | %18d | %18d\n", "Stored moon count", a->moons, b->moons);
}

int main(void) {
    size_t count, selected, first, second;
    const CelestialBody *bodies = get_bodies(&count);
    int choice;
    puts("Welcome to the Space Mission Calculator!");
    do {
        show_menu();
        if (!read_int_range("Select an option: ", 0, 12, &choice)) break;
        switch (choice) {
            case 1:
                show_body_list(bodies, count);
                break;
            case 2:
                if (choose_body(bodies, count, "Select body number: ", &selected))
                    show_body_details(&bodies[selected]);
                break;
            case 3:
                if (choose_body(bodies, count, "Select body number: ", &selected))
                    print_velocity(&bodies[selected]);
                break;
            case 4:
                if (choose_body(bodies, count, "Select body number: ", &selected))
                    print_gravity(&bodies[selected]);
                break;
            case 5: {
                double mass, g;
                if (!choose_body(bodies, count, "Select body number: ", &selected)) break;
                if (!read_positive_double("Enter your mass in kg: ", &mass)) break;
                g = surface_gravity(bodies[selected].mass_kg, bodies[selected].radius_m);
                printf("Weight on %s: %.3f N\n", bodies[selected].name, weight_newtons(mass, g));
                break;
            }
            case 6:
                if (!choose_body(bodies, count, "Select body number: ", &selected)) break;
                if (bodies[selected].orbit_type != ORBIT_SUN || bodies[selected].distance_from_sun_km <= 0.0) {
                    printf("A heliocentric circular-orbit estimate is not available for %s.\n", bodies[selected].name);
                } else {
                    double v = circular_orbital_velocity(SUN_MASS, bodies[selected].distance_from_sun_km * 1000.0);
                    printf("Approximate circular orbital velocity of %s: %.4f km/s\n", bodies[selected].name, v / 1000.0);
                }
                break;
            case 7:
                if (!choose_body(bodies, count, "Select body number: ", &selected)) break;
                if (bodies[selected].orbit_type != ORBIT_SUN || bodies[selected].distance_from_sun_km <= 0.0) {
                    printf("A heliocentric circular-orbit estimate is not available for %s.\n", bodies[selected].name);
                } else {
                    double days = circular_orbital_period_days(SUN_MASS, bodies[selected].distance_from_sun_km * 1000.0);
                    printf("Calculated orbital period for %s: %.2f days\n", bodies[selected].name, days);
                    printf("Stored reference period: %.2f days\n", bodies[selected].orbital_period_days);
                }
                break;
            case 8: {
                double speed, distance, days;
                if (!choose_body(bodies, count, "Select starting body: ", &first)) break;
                if (!choose_body(bodies, count, "Select destination body: ", &second)) break;
                if (first == second) {
                    puts("Choose two different bodies.");
                    break;
                }
                distance = fabs(bodies[first].distance_from_sun_km - bodies[second].distance_from_sun_km);
                if (distance <= 0.0) {
                    puts("The stored data does not provide a usable radial-distance estimate for this pair.");
                    break;
                }
                if (!read_positive_double("Enter constant spacecraft speed in km/s: ", &speed)) break;
                days = approximate_travel_time_days(distance, speed);
                printf("Approximate radial distance: %.3f million km\n", distance / 1.0e6);
                printf("Estimated time: %.2f days (%.3f years)\n", days, days / DAYS_PER_YEAR);
                puts("Simplified estimate only: real missions require orbital-transfer modelling.");
                break;
            }
            case 9:
                if (!choose_body(bodies, count, "Select first body: ", &first)) break;
                if (!choose_body(bodies, count, "Select second body: ", &second)) break;
                if (first == second) puts("Choose two different bodies.");
                else compare_bodies(&bodies[first], &bodies[second]);
                break;
            case 10:
                custom_body();
                break;
            case 11: {
                char path[256];
                printf("CSV output filename (e.g. planets.csv): ");
                if (!fgets(path, sizeof path, stdin)) break;
                path[strcspn(path, "\r\n")] = '\0';
                if (path[0] == '\0') strcpy(path, "planet_report.csv");
                if (export_body_report_csv(path, bodies, count))
                    printf("Exported planetary data to %s\n", path);
                else
                    printf("Could not write to '%s'. Check the path and permissions.\n", path);
                break;
            }
            case 12:
                run_self_tests();
                break;
            case 0:
                puts("Goodbye! Keep exploring.");
                break;
        }
    } while (choice != 0);
    return 0;
}
