# 🚀 Space Mission Calculator

A modular, menu-driven C application that applies classical physics equations to planetary data. This expanded version includes celestial-body comparisons, custom-body calculations, CSV export, formula self-tests, stronger input validation, and clearer separation between data, physics, and interface code.

> **Educational project:** Calculations are simplified models, not spacecraft navigation or mission-planning outputs.

## Features

- Escape velocity and surface gravity
- Weight on a selected celestial body
- Circular orbital velocity and period around the Sun
- Simplified constant-speed travel-time estimates
- Celestial-body information and side-by-side comparison
- Custom-body gravity and escape-velocity calculator
- Export of the built-in database to CSV
- Built-in sanity checks for Earth calculations
- Input validation using line-based input parsing
- Modular source files and compiler warnings

## Celestial bodies

Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, and Sun.

The database uses approximate embedded values. The Moon is classified as orbiting Earth; heliocentric circular-orbit calculations are therefore disabled for the Moon and Sun in the menu.

## Physics

| Quantity | Formula |
|---|---|
| Escape velocity | `sqrt(2 * G * M / R)` |
| Surface gravity | `G * M / (R * R)` |
| Weight | `mass * gravity` |
| Circular orbital velocity | `sqrt(G * central_mass / r)` |
| Circular orbital period | `2 * PI * sqrt(r^3 / (G * central_mass))` |
| Approximate travel time | `distance / speed` |

Constants: `G = 6.67430e-11 m^3 kg^-1 s^-2`, `PI ≈ 3.141592653589793`, and solar mass `= 1.98847e30 kg`.

## Project structure

```text
Space-Mission-Calculator/
├── include/
│   └── space.h          # Shared types and function declarations
├── src/
│   ├── main.c           # Menu and application flow
│   ├── physics.c        # Physics formulas
│   ├── planets.c        # Built-in celestial-body database
│   └── ui.c             # Input, display, CSV export, self-tests
├── Makefile
├── .gitignore
└── README.md
```

## Requirements

- GCC or a compatible C compiler
- A terminal
- `make` is optional; the project can be compiled directly with GCC

The source uses standard C11 for most functionality. Build instructions below target GCC on Linux, macOS with a suitable compiler, or Windows through WSL. Native Windows builds may need platform-specific adjustments depending on the compiler.

## Build and run

### Option A: Using Make

```bash
make
make run
```

To remove generated build outputs:

```bash
make clean
```

### Option B: Compile directly

Run this from the repository root:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/physics.c src/planets.c src/ui.c -o space_mission_calculator -lm
```

Then run:

```bash
./space_mission_calculator
```

On Windows, run the executable produced by your compiler, or use WSL for the commands above.

## Menu options

1. List celestial bodies
2. View body details
3. Calculate escape velocity
4. Calculate surface gravity
5. Calculate weight on a body
6. Calculate orbital velocity around the Sun
7. Calculate orbital period around the Sun
8. Estimate straight-line travel time
9. Compare two bodies
10. Calculate properties of a custom body
11. Export body database to CSV
12. Run formula self-tests
0. Exit

## Example values

Using the embedded Earth parameters, expected values are approximately:

- Surface gravity: `9.82 m/s^2`
- Escape velocity: `11.19 km/s`
- Weight of a 70 kg object: `687 N`

Select option `12` to run the built-in formula sanity checks.

## CSV export

Choose menu option `11` and enter a filename, for example `planets.csv`. The application writes the embedded celestial-body data as comma-separated values that can be opened in spreadsheet software.

## Model assumptions and limitations

- Surface gravity and escape velocity use a spherical-body approximation based on the stored mass and radius.
- Orbital velocity and period assume a circular orbit around the Sun.
- Travel time uses the absolute difference between average distances from the Sun and assumes constant speed. It does not calculate actual planet-to-planet distance or a spacecraft transfer trajectory.
- The stored planetary data are approximate and may need updating for scientific use.
- The moon counts are embedded reference values and may change as astronomical catalogues are updated.
- The custom-body tool calculates gravity and escape velocity only; it does not add the custom body to the built-in database.
- The self-tests are simple numerical sanity checks, not a comprehensive automated test suite.

## Future roadmap

- [ ] Add a dedicated unit-conversion menu (km/m, km/s/m/s, days/years)
- [ ] Add a configurable body database loaded from CSV
- [ ] Add more automated tests and edge-case tests
- [ ] Add orbital eccentricity and a better distance model
- [ ] Add a simple graphical interface
- [ ] Add portable terminal styling and platform-specific build targets
- [ ] Add report metadata and user-selected output locations

## Learning goals

This project demonstrates:

- Structures and enumerated types
- Pointers and arrays
- Function declarations and modular compilation
- Input validation and error handling
- Mathematical functions and unit conversion
- CSV file output
- Basic numerical self-testing
- Separation of application logic, data, and interface code

## Author

**Snehankur Mondal**

GitHub: [@mondalsnehankur](https://github.com/mondalsnehankur)

## Disclaimer

This program is intended for learning C programming and introductory physics. Do not use its outputs for real spacecraft navigation, engineering decisions, or mission planning.
