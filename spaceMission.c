/*
============================================================
            SPACE MISSION CALCULATOR
============================================================

Description:
    A C-based application that performs common space and planetary calculations using real physics equations.

C Concepts Used:
    - Structures
    - Dynamic memory allocation (malloc/free)
    - Pointers
    - Functions
    - Arrays
    - Loops
    - Switch-case
    - Input validation
    - Mathematical functions
    - ANSI escape codes for terminal color/formatting

Physics Concepts:
    - Escape velocity
    - Planetary gravity
    - Weight
    - Newton's law of gravitation
    - Orbital velocity
    - Orbital period
    - Space travel time
    - Planet comparison
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/* Gravitational constant */
#define G 6.67430e-11

/* Mathematical constant */
#define PI 3.14159265358979323846

/* Mass of the Sun */
#define SUN_MASS 1.98847e30

/*
    ANSI escape codes.
    These are special character sequences that a terminal
    interprets as formatting commands instead of printing
    them as visible text. "\033" is the ESC character, and
    everything after "[" tells the terminal what to do
    (change color, reset formatting, etc).
*/
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_MAGENTA "\033[35m"

// Structure used to store information about a celestial body.
typedef struct{
    char name[20];
    double mass;                // Mass in kilograms
    double radius;              // Radius in metres
    double distanceFromSun;     // Average distance from Sun in million km
    double orbitalPeriod;       // Orbital period in Earth days
    int moons;                  // Number of known natural satellites
} Planet;

// Function declarations
void initializePlanets(Planet *planets);
void showBanner(void);
void clearScreen(void);
void displayMenu(void);
void displayPlanetList(const Planet *planets, int count);
int selectPlanet(const Planet *planets, int count);

void planetInformation(const Planet *planet);
void calculateEscapeVelocity(const Planet *planet);
void calculateGravity(const Planet *planet);
void calculateWeight(const Planet *planet);
void calculateOrbitalVelocity(const Planet *planet);
void calculateOrbitalPeriod(const Planet *planet);
void calculateTravelTime(const Planet *planets, int count);
void comparePlanets(const Planet *planets, int count);

void printSectionHeader(const char *title);
void showProgressBar(void);
void clearInputBuffer(void);

// Initialize the planetary database.
// Values are approximate and are primarily intended for educational calculations.
void initializePlanets(Planet *planets){
    planets[0] = (Planet){
        "Mercury",
        3.3011e23,
        2.4397e6,
        57.9,
        87.97,
        0
    };
    planets[1] = (Planet){
        "Venus",
        4.8675e24,
        6.0518e6,
        108.2,
        224.70,
        0
    };
    planets[2] = (Planet){
        "Earth",
        5.9722e24,
        6.3710e6,
        149.6,
        365.25,
        1
    };
    planets[3] = (Planet){
        "Moon",
        7.342e22,
        1.7374e6,
        149.6,
        27.32,
        0
    };
    planets[4] = (Planet){
        "Mars",
        6.4171e23,
        3.3895e6,
        227.9,
        687.0,
        2
    };
    planets[5] = (Planet){
        "Jupiter",
        1.8982e27,
        6.9911e7,
        778.5,
        4332.59,
        95
    };
    planets[6] = (Planet){
        "Saturn",
        5.6834e26,
        5.8232e7,
        1434.0,
        10759.22,
        146
    };
    planets[7] = (Planet){
        "Uranus",
        8.6810e25,
        2.5362e7,
        2871.0,
        30688.5,
        28
    };
    planets[8] = (Planet){
        "Neptune",
        1.02413e26,
        2.4622e7,
        4495.1,
        60182.0,
        16
    };
    planets[9] = (Planet){
        "Sun",
        1.98847e30,
        6.9634e8,
        0.0,
        0.0,
        8
    };
}

/*
    Clear the terminal screen.
    "cls" is the Windows command, "clear" is the Linux/Mac command.
    The #ifdef block picks the right one at compile time depending
    on the platform the program is built on.
*/
void clearScreen(void){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Print a simple ASCII banner once when the program starts.
void showBanner(void){
    printf(COLOR_CYAN COLOR_BOLD);
    printf("\n");
    printf("        /\\\n");
    printf("       /  \\\n");
    printf("      / /\\ \\\n");
    printf("     /_/  \\_\\\n");
    printf("       |  |\n");
    printf("      /|  |\\\n");
    printf("     ^ |  | ^\n");
    printf("       ~~~~\n");
    printf("   SPACE MISSION CALCULATOR\n");
    printf(COLOR_RESET);
    printf(COLOR_YELLOW "   -- physics-based planetary toolkit --\n" COLOR_RESET);
}

/*
    Print a box-drawn section header used by every calculation
    function. Centralising this in one function avoids repeating
    the same border-printing code everywhere.
*/
void printSectionHeader(const char *title){
    printf("\n" COLOR_MAGENTA "+----------------------------------------+\n");
    printf("  %s\n", title);
    printf("+----------------------------------------+" COLOR_RESET "\n");
}

/*
    A small cosmetic progress bar used for the travel time
    calculation, to make a "space journey" feel less like an
    instant printf and more like something is being computed.
    usleep() pauses execution for a given number of microseconds.
*/
void showProgressBar(void){
    printf("\nCalculating trajectory: ");
    fflush(stdout);
    for(int i = 0; i < 20; i++){
        printf(COLOR_GREEN "#" COLOR_RESET);
        fflush(stdout);
        usleep(40000); // 40ms per step -> ~0.8s total
    }
    printf("\n");
}

// Displaying the Main Menu.
void displayMenu(void){
    printf("\n");
    printf(COLOR_CYAN "+----------------------------------------+\n");
    printf("|        SPACE MISSION CALCULATOR         |\n");
    printf("+----------------------------------------+" COLOR_RESET "\n");
    printf(COLOR_YELLOW "1." COLOR_RESET " Escape Velocity\n");
    printf(COLOR_YELLOW "2." COLOR_RESET " Orbital Velocity\n");
    printf(COLOR_YELLOW "3." COLOR_RESET " Orbital Period\n");
    printf(COLOR_YELLOW "4." COLOR_RESET " Weight on Another Planet\n");
    printf(COLOR_YELLOW "5." COLOR_RESET " Planetary Gravity\n");
    printf(COLOR_YELLOW "6." COLOR_RESET " Space Travel Time\n");
    printf(COLOR_YELLOW "7." COLOR_RESET " Planet Information\n");
    printf(COLOR_YELLOW "8." COLOR_RESET " Compare Planets\n");
    printf(COLOR_YELLOW "9." COLOR_RESET " Exit\n");
    printf(COLOR_CYAN "+----------------------------------------+\n" COLOR_RESET);
}

// Display the list of celestial bodies.
void displayPlanetList(const Planet *planets, int count){
    printf("\n" COLOR_GREEN "Available Celestial Bodies:" COLOR_RESET "\n");
    printf("----------------------------------------\n");

    // Loop through the array of planets and display their names.
    for(int i = 0; i < count; i++){
        printf("%2d. %s\n", i + 1, planets[i].name);
    }
    printf("----------------------------------------\n");
}

// Allows the user to select the planet from the list of celestial bodies.
int selectPlanet(const Planet *planets, int count){
    int choice;
    displayPlanetList(planets, count);
    printf("Enter choice: ");

    while(scanf("%d", &choice) != 1 || choice < 1 || choice > count){
        printf("Invalid choice. Please enter a number from 1 to %d: ", count);
        clearInputBuffer();
    }

    clearInputBuffer();
    return choice - 1;
}

// Display complete information about a celestial body.
void planetInformation(const Planet *planet){
    char title[64];
    snprintf(title, sizeof(title), "%s INFORMATION", planet->name);
    printSectionHeader(title);
    printf("Mass              : %.4e kg\n", planet->mass);
    printf("Radius            : %.2e m\n", planet->radius);
    printf("Distance from Sun : %.2f million km\n", planet->distanceFromSun);
    printf("Orbital Period    : %.2f days\n", planet->orbitalPeriod);
    printf("Number of Moons   : %d\n", planet->moons);
}

/*
    Calculate escape velocity.
        Ve = sqrt(2GM / R)
    Result is converted from m/s to km/s.
*/
void calculateEscapeVelocity(const Planet *planet){
    double velocity;

    velocity = sqrt((2.0 * G * planet->mass) / planet->radius);

    printSectionHeader("ESCAPE VELOCITY");
    printf("Celestial Body : %s\n", planet->name);
    printf("Escape Velocity: %.2f km/s\n", velocity / 1000.0);
}

/*
    Calculate surface gravity.
        g = GM / R^2
    Result is given in m/s^2.
*/
void calculateGravity(const Planet *planet){
    double gravity;

    gravity = (G * planet->mass) / (planet->radius * planet->radius);

    printSectionHeader("PLANETARY GRAVITY");
    printf("Celestial Body : %s\n", planet->name);
    printf("Surface Gravity: %.2f m/s^2\n", gravity);
}

/*
    Calculate a person's weight on the selected
    celestial body.
        Weight = Mass × Gravity
*/
void calculateWeight(const Planet *planet){
    double mass;
    double gravity;
    double weight;

    printf("\nEnter your mass in kilograms: ");

    while(scanf("%lf", &mass) != 1 || mass <= 0){
        printf("Invalid mass. Please enter a positive value: ");
        clearInputBuffer();
    }

    clearInputBuffer();

    gravity = (G * planet->mass) / (planet->radius * planet->radius);
    weight = mass * gravity;

    printSectionHeader("WEIGHT CALCULATOR");
    printf("Celestial Body : %s\n", planet->name);
    printf("Mass           : %.2f kg\n", mass);
    printf("Gravity        : %.2f m/s^2\n", gravity);
    printf("Weight         : %.2f N\n", weight);
}

/*
    Calculate orbital velocity around the Sun.

        v = sqrt(GM / r)

    Here:
        G = Gravitational constant
        M = Mass of the Sun
        r = Distance from the Sun

    The calculation assumes a circular orbit.
*/
void calculateOrbitalVelocity(const Planet *planet){
    double distance;
    double velocity;

    if(planet->distanceFromSun <= 0){
        printf("\nOrbital velocity cannot be calculated for %s.\n", planet->name);
        printf("No valid heliocentric distance is available.\n");
        return;
    }

    // Convert million kilometres to metres.
    distance = planet->distanceFromSun * 1.0e9;

    velocity = sqrt((G * SUN_MASS) / distance);

    printSectionHeader("ORBITAL VELOCITY");
    printf("Celestial Body  : %s\n", planet->name);
    printf("Distance        : %.2f million km\n", planet->distanceFromSun);
    printf("Orbital Velocity: %.2f km/s\n", velocity / 1000.0);
    printf("\nAssumption: Circular orbit around the Sun.\n");
}

/*
    Calculate orbital period around the Sun.

        T = 2π sqrt(r^3 / GM)

    Result is converted from seconds to Earth days.

    The calculation assumes a circular orbit.
*/
void calculateOrbitalPeriod(const Planet *planet){
    double distance;
    double periodSeconds;
    double periodDays;

    if(planet->distanceFromSun <= 0){
        printf("\nOrbital period cannot be calculated for %s.\n", planet->name);
        printf("No valid heliocentric distance is available.\n");
        return;
    }

    // Convert million kilometres to metres.
    distance = planet->distanceFromSun * 1.0e9;

    periodSeconds = 2.0 * PI * sqrt(
        (distance * distance * distance) /
        (G * SUN_MASS)
    );

    periodDays = periodSeconds / (60.0 * 60.0 * 24.0);

    printSectionHeader("ORBITAL PERIOD");
    printf("Celestial Body : %s\n", planet->name);
    printf("Calculated     : %.2f days\n", periodDays);
    printf("Database Value : %.2f days\n", planet->orbitalPeriod);
    printf("\nAssumption: Circular orbit around the Sun.\n");
}

/*
    Calculate approximate space travel time.

        Time = Distance / Speed

    The distance is estimated using the difference between
    the average heliocentric distances of the two bodies.

    This is a simplified educational calculation.
    Actual spacecraft missions use orbital transfer
    trajectories and planetary motion.
*/
void calculateTravelTime(const Planet *planets, int count){
    int source;
    int destination;
    double distance;
    double speed;
    double timeSeconds;
    double timeHours;
    double timeDays;
    double timeYears;

    printf("\nSelect starting body:\n");
    source = selectPlanet(planets, count);

    printf("\nSelect destination body:\n");
    destination = selectPlanet(planets, count);

    if(source == destination){
        printf("\nStarting body and destination cannot be the same.\n");
        return;
    }

    /*
        Calculate difference in average distance from the Sun.

        distanceFromSun is stored in million km.
    */
    distance = fabs(
        planets[destination].distanceFromSun -
        planets[source].distanceFromSun
    );

    // Convert million km to km.
    distance *= 1.0e6;

    if(distance <= 0){
        printf("\nTravel distance cannot be calculated using the current database.\n");
        return;
    }

    printf("\nEnter spacecraft speed in km/s: ");

    while(scanf("%lf", &speed) != 1 || speed <= 0){
        printf("Invalid speed. Enter a positive value: ");
        clearInputBuffer();
    }

    clearInputBuffer();

    /*
        Since both distance and speed are in kilometres,
        the result is directly obtained in seconds.
    */
    timeSeconds = distance / speed;
    timeHours = timeSeconds / 3600.0;
    timeDays = timeHours / 24.0;
    timeYears = timeDays / 365.25;

    // Cosmetic-only: gives a sense of "computing" before the result appears.
    showProgressBar();

    printSectionHeader("SPACE TRAVEL TIME");
    printf("Starting Body   : %s\n", planets[source].name);
    printf("Destination     : %s\n", planets[destination].name);
    printf("Approx. Distance: %.2f million km\n", distance / 1.0e6);
    printf("Spacecraft Speed: %.2f km/s\n", speed);

    printf("\nTravel Time:\n");
    printf("Hours           : %.2f hours\n", timeHours);
    printf("Days            : %.2f days\n", timeDays);
    printf("Years           : %.2f years\n", timeYears);

    printf("\nNote: This is a simplified straight-line estimate.\n");
    printf("Actual missions use orbital transfer trajectories.\n");
}

/*
    Compare two selected celestial bodies.

    The comparison includes:
        - Mass
        - Radius
        - Distance from Sun
        - Orbital period
        - Number of moons
        - Surface gravity
        - Escape velocity
*/
void comparePlanets(const Planet *planets, int count){
    int first;
    int second;
    double gravity1;
    double gravity2;
    double escape1;
    double escape2;

    printf("\nSelect first celestial body:\n");
    first = selectPlanet(planets, count);

    printf("\nSelect second celestial body:\n");
    second = selectPlanet(planets, count);

    if(first == second){
        printf("\nPlease select two different celestial bodies.\n");
        return;
    }

    // Calculate surface gravity for both bodies.
    gravity1 = (G * planets[first].mass) /
               (planets[first].radius * planets[first].radius);

    gravity2 = (G * planets[second].mass) /
               (planets[second].radius * planets[second].radius);

    // Calculate escape velocity for both bodies.
    escape1 = sqrt(
        (2.0 * G * planets[first].mass) /
        planets[first].radius
    );

    escape2 = sqrt(
        (2.0 * G * planets[second].mass) /
        planets[second].radius
    );

    printf("\n");
    printf(COLOR_MAGENTA "====================================================\n");
    printf("                 PLANET COMPARISON\n");
    printf("====================================================" COLOR_RESET "\n");

    printf(COLOR_BOLD "%-25s %-15s %-15s" COLOR_RESET "\n",
           "Property",
           planets[first].name,
           planets[second].name);

    printf("----------------------------------------------------\n");

    printf("%-25s %-15.4e %-15.4e\n",
           "Mass (kg)",
           planets[first].mass,
           planets[second].mass);

    printf("%-25s %-15.2e %-15.2e\n",
           "Radius (m)",
           planets[first].radius,
           planets[second].radius);

    printf("%-25s %-15.2f %-15.2f\n",
           "Distance from Sun",
           planets[first].distanceFromSun,
           planets[second].distanceFromSun);

    printf("%-25s %-15.2f %-15.2f\n",
           "Orbital Period (days)",
           planets[first].orbitalPeriod,
           planets[second].orbitalPeriod);

    printf("%-25s %-15d %-15d\n",
           "Number of Moons",
           planets[first].moons,
           planets[second].moons);

    printf("%-25s %-15.2f %-15.2f\n",
           "Surface Gravity (m/s^2)",
           gravity1,
           gravity2);

    printf("%-25s %-15.2f %-15.2f\n",
           "Escape Velocity (km/s)",
           escape1 / 1000.0,
           escape2 / 1000.0);

    printf(COLOR_MAGENTA "====================================================\n" COLOR_RESET);
}

// Clear the input buffer to handle invalid inputs and prevent infinite loops.
void clearInputBuffer(void){
    int character;

    while((character = getchar()) != '\n' && character != EOF){
        /* Discard input */
    }
}

int main(void){
    const int planetCount = 10; // Total no:of celestial bodies in our solar system.
    /*
        Dynamically allocate memory for the planetary database.
        malloc() allocates memory at runtime.
    */
    Planet *planets = malloc(planetCount * sizeof(Planet));
    // To check if the memory allocation was successful.
    if(planets == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }
    /*
        Fill the dynamically allocated array.
    */
    initializePlanets(planets);

    int choice;
    int selectedPlanet;

    clearScreen();
    showBanner();

    // Main Program Loop.
    do{
        displayMenu();

        printf("\nEnter choice: ");

        while(scanf("%d", &choice) != 1 || choice < 1 || choice > 9){
            printf("Invalid choice. Please enter 1-9: ");
            clearInputBuffer();
        }

        clearInputBuffer();

        // Perform the operation selected by the user.
        switch(choice){
            case 1:
                selectedPlanet = selectPlanet(planets, planetCount);
                calculateEscapeVelocity(&planets[selectedPlanet]);
                break;

            case 2:
                selectedPlanet = selectPlanet(planets, planetCount);
                calculateOrbitalVelocity(&planets[selectedPlanet]);
                break;

            case 3:
                selectedPlanet = selectPlanet(planets, planetCount);
                calculateOrbitalPeriod(&planets[selectedPlanet]);
                break;

            case 4:
                selectedPlanet = selectPlanet(planets, planetCount);
                calculateWeight(&planets[selectedPlanet]);
                break;

            case 5:
                selectedPlanet = selectPlanet(planets, planetCount);
                calculateGravity(&planets[selectedPlanet]);
                break;

            case 6:
                calculateTravelTime(planets, planetCount);
                break;

            case 7:
                selectedPlanet = selectPlanet(planets, planetCount);
                planetInformation(&planets[selectedPlanet]);
                break;

            case 8:
                comparePlanets(planets, planetCount);
                break;

            case 9:
                printf(COLOR_CYAN "\nExiting Space Mission Calculator...\n" COLOR_RESET);
                break;
        }
    }while(choice != 9);

    // Releases the dynamically allocated memory for the planetary database.
    free(planets);

    return 0;
}

/*
    ============================================================
                    VARIABLE DESCRIPTION
    ============================================================

    Variable / Member          Data Type       Description
    ------------------------------------------------------------
    name                       char[20]        Name of the celestial body

    mass                       double          Mass in kilograms

    radius                     double          Radius in metres

    distanceFromSun            double          Distance from Sun
                                                in million kilometres

    orbitalPeriod              double          Orbital period in days

    moons                      int             Number of natural
                                                satellites

    planets                    Planet*         Dynamically allocated
                                                array of celestial bodies

    planetCount                int             Number of celestial bodies

    choice                     int             User's menu selection

    selectedPlanet             int             Index of selected body

    velocity                   double          Calculated velocity

    gravity                    double          Surface gravity

    mass                       double          User's mass in kilograms

    weight                     double          Calculated weight

    distance                   double          Distance between
                                                celestial bodies

    speed                      double          Spacecraft speed

    timeSeconds                double          Travel time in seconds

    timeHours                  double          Travel time in hours

    timeDays                   double          Travel time in days

    timeYears                  double          Travel time in years

    periodSeconds              double          Orbital period in seconds

    periodDays                 double          Orbital period in days

    escape1                    double          Escape velocity of
                                                first body

    escape2                    double          Escape velocity of
                                                second body

    gravity1                   double          Gravity of first body

    gravity2                   double          Gravity of second body

    character                  int             Stores input characters
                                                while clearing buffer

    G                          constant        Universal gravitational
                                                constant

    PI                         constant        Mathematical constant π

    SUN_MASS                   constant        Mass of the Sun

    COLOR_*                    constant        ANSI escape codes used
                                                for colored terminal output

    ============================================================
*/