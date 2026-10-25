#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int read_int_range(const char *prompt, int min, int max, int *out) {
    char line[128], *end;
    long value;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0;
        errno = 0;
        value = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;
        if (errno == 0 && end != line && *end == '\0' && value >= min && value <= max) {
            *out = (int)value;
            return 1;
        }
        printf("Invalid input. Enter a whole number from %d to %d.\n", min, max);
    }
}

int read_positive_double(const char *prompt, double *out) {
    char line[128], *end;
    double value;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0;
        errno = 0;
        value = strtod(line, &end);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;
        if (errno == 0 && end != line && *end == '\0' && isfinite(value) && value > 0.0) {
            *out = value;
            return 1;
        }
        printf("Invalid input. Enter a finite number greater than zero.\n");
    }
}

void pause_for_enter(void) {
    char line[8];
    printf("\nPress Enter to continue...");
    (void)fgets(line, sizeof line, stdin);
}

void show_menu(void) {
    puts("\n=================================================");
    puts("             SPACE MISSION CALCULATOR");
    puts("=================================================");
    puts(" 1. List celestial bodies");
    puts(" 2. View body details");
    puts(" 3. Calculate escape velocity");
    puts(" 4. Calculate surface gravity");
    puts(" 5. Calculate weight on a body");
    puts(" 6. Calculate orbital velocity around the Sun");
    puts(" 7. Calculate orbital period around the Sun");
    puts(" 8. Estimate straight-line travel time");
    puts(" 9. Compare two bodies");
    puts("10. Calculate properties of a custom body");
    puts("11. Export body database to CSV");
    puts("12. Run formula self-tests");
    puts(" 0. Exit");
    puts("-------------------------------------------------");
}

void show_body_list(const CelestialBody *bodies, size_t count) {
    size_t i;
    puts("\nAvailable celestial bodies:");
    for (i = 0; i < count; ++i) printf(" %2zu. %s\n", i + 1, bodies[i].name);
}

void show_body_details(const CelestialBody *b) {
    printf("\n--- %s ---\n", b->name);
    printf("Mass:                  %.5e kg\n", b->mass_kg);
    printf("Mean radius:            %.5e m\n", b->radius_m);
    printf("Average distance from Sun: %.3f million km\n", b->distance_from_sun_km / 1.0e6);
    printf("Stored orbital period:  %.2f days\n", b->orbital_period_days);
    printf("Stored moon count:      %d\n", b->moons);
    printf("Orbit classification:   %s\n", b->orbit_type == ORBIT_SUN ? "Around the Sun" :
           (b->orbit_type == ORBIT_EARTH ? "Around Earth" : "Not applicable"));
    printf("Notes: %s\n", b->notes);
}

int export_body_report_csv(const char *path, const CelestialBody *bodies, size_t count) {
    FILE *fp = fopen(path, "w");
    size_t i;
    if (!fp) return 0;
    fprintf(fp, "name,mass_kg,radius_m,distance_from_sun_km,orbital_period_days,moons,orbit_type\n");
    for (i = 0; i < count; ++i) {
        const char *orbit = bodies[i].orbit_type == ORBIT_SUN ? "Sun" :
                            (bodies[i].orbit_type == ORBIT_EARTH ? "Earth" : "None");
        fprintf(fp, "%s,%.8e,%.8e,%.3f,%.3f,%d,%s\n",
                bodies[i].name, bodies[i].mass_kg, bodies[i].radius_m,
                bodies[i].distance_from_sun_km, bodies[i].orbital_period_days,
                bodies[i].moons, orbit);
    }
    return fclose(fp) == 0;
}

void run_self_tests(void) {
    double g = surface_gravity(5.9722e24, 6.3710e6);
    double ve = escape_velocity(5.9722e24, 6.3710e6) / 1000.0;
    int pass_g = fabs(g - 9.82) < 0.1;
    int pass_ve = fabs(ve - 11.19) < 0.1;
    printf("\nFormula self-tests\n");
    printf("[%s] Earth surface gravity: %.3f m/s^2 (expected about 9.82)\n", pass_g ? "PASS" : "FAIL", g);
    printf("[%s] Earth escape velocity: %.3f km/s (expected about 11.19)\n", pass_ve ? "PASS" : "FAIL", ve);
    printf("[%s] 70 kg weight on Earth: %.1f N (expected about 687)\n",
           fabs(weight_newtons(70.0, g) - 687.0) < 10.0 ? "PASS" : "FAIL",
           weight_newtons(70.0, g));
}
