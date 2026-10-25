# 🚀 Space Mission Calculator

A menu-driven **C application that combines programming fundamentals with classical physics** to perform planetary calculations and explore selected properties of celestial bodies in our Solar System.

The project calculates escape velocity, surface gravity, weight on another celestial body, orbital velocity, orbital period, and approximate space-travel time. It also provides planetary information and allows users to compare two celestial bodies through a formatted terminal interface.

Built as a hands-on learning project, it demonstrates how mathematical equations, structured data, functions, pointers, and dynamic memory allocation can be used to solve practical computational problems.

---

## 📌 Table of Contents

- [Project Overview](#-project-overview)
- [Features](#-features)
- [Celestial Bodies Included](#-celestial-bodies-included)
- [Physics and Mathematical Formulas](#-physics-and-mathematical-formulas)
- [C Programming Concepts Demonstrated](#-c-programming-concepts-demonstrated)
- [Technologies and Libraries](#-technologies-and-libraries)
- [Getting Started](#-getting-started)
- [How to Use](#-how-to-use)
- [Project Structure](#-project-structure)
- [Sample Calculations](#-sample-calculations)
- [Assumptions and Limitations](#-assumptions-and-limitations)
- [Future Improvements](#-future-improvements)
- [Learning Outcomes](#-learning-outcomes)
- [Author](#-author)

---

## 🌌 Project Overview

The **Space Mission Calculator** is an interactive command-line application developed in C. It uses physical constants and approximate astronomical data to perform calculations related to gravity, planetary motion, and space travel.

Instead of relying on fixed outputs, the application accepts user input, retrieves information about a selected celestial body, applies the appropriate mathematical formula, and displays the result.

The program maintains a small planetary database using a custom C structure and dynamically allocated memory. Its menu-driven interface allows users to perform multiple calculations during a single session.

### Project Objectives

- Apply fundamental C programming concepts to a practical application.
- Implement classical physics equations using mathematical operations.
- Organize astronomical information using structures and arrays.
- Handle user input and validate numeric choices.
- Display calculation results in a readable, formatted terminal interface.
- Explore the relationships between mass, radius, gravity, velocity, and orbital motion.

---

## ✨ Features

### 1. Escape Velocity Calculator

Calculates the theoretical minimum speed required for an object to escape a celestial body's gravitational field without additional propulsion, ignoring atmospheric drag and other external influences.

**Output:** Escape velocity in kilometres per second (km/s).

### 2. Orbital Velocity Calculator

Estimates the orbital speed of a body moving around the Sun under the assumption of a circular orbit.

**Output:** Approximate orbital velocity in km/s.

### 3. Orbital Period Calculator

Calculates the theoretical orbital period around the Sun using the body's average heliocentric distance.

The program also displays the orbital period stored in its astronomical data so the two values can be compared.

**Output:** Calculated and stored orbital periods in Earth days.

### 4. Weight on Another Celestial Body

Accepts a person's mass in kilograms and calculates the corresponding gravitational force on a selected celestial body.

**Output:** Mass in kilograms, surface gravity in m/s², and weight in newtons (N).

### 5. Planetary Gravity Calculator

Calculates the approximate gravitational acceleration at the surface of a celestial body using its mass and radius.

**Output:** Surface gravity in metres per second squared (m/s²).

### 6. Space Travel Time Estimator

Estimates travel time between two selected celestial bodies using the difference between their average distances from the Sun and a user-provided spacecraft speed.

**Output:**
- Estimated distance in million kilometres
- Spacecraft speed in km/s
- Travel time in hours
- Travel time in days
- Travel time in years

A simple terminal progress bar is displayed before the result.

> **Note:** This is a simplified educational estimate, not a realistic spacecraft mission trajectory calculation.

### 7. Celestial Body Information

Displays the stored information for a selected body, including:

- Name
- Mass
- Radius
- Average distance from the Sun
- Orbital period
- Number of moons or natural satellites recorded in the program

### 8. Planet Comparison

Compares two different celestial bodies in a formatted table.

The comparison includes:

| Property | Unit |
|---|---|
| Mass | kg |
| Radius | m |
| Average distance from the Sun | Million km |
| Orbital period | Earth days |
| Number of moons | Count |
| Surface gravity | m/s² |
| Escape velocity | km/s |

### 9. Interactive Terminal Interface

The application includes:
- A space-themed ASCII banner
- A numbered main menu
- Colourful terminal output using ANSI escape sequences
- Formatted section headers
- Input validation for menu selections and numeric inputs
- A continuous menu loop until the user chooses to exit

---

## 🪐 Celestial Bodies Included

The application stores information about ten celestial bodies:

| No. | Celestial body |
|---:|---|
| 1 | Mercury |
| 2 | Venus |
| 3 | Earth |
| 4 | Moon |
| 5 | Mars |
| 6 | Jupiter |
| 7 | Saturn |
| 8 | Uranus |
| 9 | Neptune |
| 10 | Sun |

The database contains approximate values for mass, radius, average distance from the Sun, orbital period, and moon count.

These values are embedded in the source code and initialized when the application starts. They are intended for educational calculations rather than precision astronomical analysis.

---

## 🧮 Physics and Mathematical Formulas

The calculator implements the following equations from classical physics.

### 1. Escape Velocity

The escape velocity of a spherical body is calculated as:

\[
v_e = \sqrt{\frac{2GM}{R}}
\]

Where:

- \(v_e\) = escape velocity in m/s
- \(G\) = universal gravitational constant
- \(M\) = mass of the celestial body in kg
- \(R\) = radius of the celestial body in m

The result is divided by 1,000 to convert m/s into km/s.

### 2. Surface Gravity

The gravitational acceleration at the surface is calculated using:

\[
g = \frac{GM}{R^2}
\]

Where:

- \(g\) = surface gravitational acceleration in m/s²
- \(G\) = universal gravitational constant
- \(M\) = mass in kg
- \(R\) = radius in m

### 3. Weight on a Celestial Body

The weight of an object is calculated using:

\[
W = mg
\]

Where:

- \(W\) = weight in newtons (N)
- \(m\) = user's mass in kg
- \(g\) = surface gravity in m/s²

Mass remains the same when moving between celestial bodies, while weight changes with the local gravitational acceleration.

### 4. Orbital Velocity

For a circular orbit around the Sun, the calculator uses:

\[
v = \sqrt{\frac{GM_{\odot}}{r}}
\]

Where:

- \(v\) = orbital velocity in m/s
- \(G\) = universal gravitational constant
- \(M_{\odot}\) = mass of the Sun
- \(r\) = average heliocentric distance in m

The result is converted to km/s.

### 5. Orbital Period

The orbital period for an ideal circular orbit around the Sun is calculated using:

\[
T = 2\pi\sqrt{\frac{r^3}{GM_{\odot}}}
\]

Where:

- \(T\) = orbital period in seconds
- \(r\) = distance from the Sun in metres
- \(G\) = universal gravitational constant
- \(M_{\odot}\) = mass of the Sun

The result is converted into Earth days by dividing by 86,400.

### 6. Approximate Space Travel Time

The program estimates the distance between two celestial bodies using the difference between their average distances from the Sun:

\[
d = |r_2-r_1|
\]

It then calculates travel time using:

\[
t = \frac{d}{v}
\]

Where:

- \(d\) = estimated distance in kilometres
- \(v\) = user-entered spacecraft speed in km/s
- \(t\) = estimated travel time in seconds

The result is converted into hours, days, and years.

This method assumes a simplified distance and constant speed. Actual interplanetary travel requires consideration of orbital motion, transfer trajectories, acceleration, deceleration, and other mission constraints.

### Physical Constants Used

| Constant | Value | Unit |
|---|---:|---|
| Universal gravitational constant, \(G\) | \(6.67430 \times 10^{-11}\) | m³ kg⁻¹ s⁻² |
| Mathematical constant, \(\pi\) | Approximately 3.141592653589793 | Dimensionless |
| Mass of the Sun, \(M_{\odot}\) | \(1.98847 \times 10^{30}\) | kg |

---

## 💻 C Programming Concepts Demonstrated

This project provides practical experience with several important concepts in the C programming language.

| Concept | Application in the project |
|---|---|
| Structures (`struct`) | Stores properties of celestial bodies in the `Planet` structure. |
| Pointers | Passes planetary data to functions without copying the entire structure. |
| Dynamic memory allocation | Allocates memory for the planetary database using `malloc()`. |
| Memory management | Releases allocated memory using `free()`. |
| Functions | Separates individual calculations and interface operations into reusable functions. |
| Arrays | Stores and accesses multiple celestial bodies. |
| Loops | Iterates through planetary data and maintains the main menu. |
| Conditional statements | Validates inputs and checks special cases. |
| `switch-case` | Routes menu selections to the corresponding operation. |
| Input validation | Rejects invalid menu choices, non-numeric input, and non-positive mass or speed values. |
| Mathematical functions | Uses `sqrt()` and `fabs()` from the C mathematics library. |
| Formatted I/O | Uses `printf()`, `scanf()`, and `snprintf()` to display and process information. |
| Preprocessor directives | Defines constants, colour codes, and platform-specific screen-clearing behaviour. |
| ANSI escape sequences | Adds colour and formatting to terminal output. |
| Dynamic data initialization | Populates the planetary database at runtime. |

The program also uses a helper function to clear unwanted characters from the input buffer and a separate function to generate a simple progress-bar effect.

---

## 🛠️ Technologies and Libraries

**Programming language:** C

**Core libraries:**

- `stdio.h` — input and output
- `stdlib.h` — memory allocation and system utilities
- `math.h` — mathematical functions
- `unistd.h` — `usleep()` for the terminal progress-bar delay on compatible POSIX systems

**Development tools:**

- A C compiler such as GCC
- A terminal or command-line environment
- Git and GitHub for source-code management

---

## 🚀 Getting Started

Follow these steps to compile and run the project locally.

### Prerequisites

1. Install a C compiler, such as GCC.
2. Install Git if you want to clone the repository.
3. Use a terminal that supports ANSI colour sequences.

The current source code includes `unistd.h` and uses `usleep()`, so the build instructions below target a compatible POSIX environment, such as Linux or a suitable macOS development setup. Native Windows compilers may require portability changes.

### Step 1: Clone the Repository

Replace the placeholder below with your actual GitHub repository URL if the project is stored in a different repository.

```bash
git clone <YOUR-REPOSITORY-URL>
```

### Step 2: Navigate to the Project Directory

```bash
cd <YOUR-PROJECT-DIRECTORY>
```

### Step 3: Compile the Program

Assuming your C source file is named `main.c`, run:

```bash
gcc main.c -o space_mission_calculator -lm
```

**Explanation:**

- `gcc` invokes the GNU C compiler.
- `main.c` is the source file; replace it with your actual filename if different.
- `-o space_mission_calculator` specifies the executable's name.
- `-lm` links the mathematics library required for functions such as `sqrt()` and `fabs()`.

### Step 4: Run the Program

On Linux or another compatible POSIX environment:

```bash
./space_mission_calculator
```

On macOS, use the same command if the executable was built successfully.

### Windows Compatibility

The code includes a Windows-specific screen-clearing command, but the use of `unistd.h` and `usleep()` means the source is not fully portable to native Windows compilers as written.

You can use a compatible POSIX environment, such as WSL, or adapt the delay function and related platform-specific code before compiling natively on Windows.

---

## 🎮 How to Use

When the application starts, it displays a space-themed banner followed by the main menu.

```text
----------------------------------------
        SPACE MISSION CALCULATOR
----------------------------------------
1. Escape Velocity
2. Orbital Velocity
3. Orbital Period
4. Weight on Another Planet
5. Planetary Gravity
6. Space Travel Time
7. Planet Information
8. Compare Planets
9. Exit
----------------------------------------

Enter choice:
```

*The output above is illustrative; spacing and colours may differ in your terminal.*

### Example Workflow: Calculate Escape Velocity

1. Select option `1`.
2. Choose a celestial body from the displayed list.
3. The application calculates its escape velocity.
4. The result is displayed in km/s.

### Example Workflow: Calculate Weight

1. Select option `4`.
2. Choose a celestial body.
3. Enter a positive mass in kilograms.
4. The application calculates surface gravity and the corresponding weight.

### Example Workflow: Compare Celestial Bodies

1. Select option `8`.
2. Choose the first celestial body.
3. Choose a different second body.
4. Review the comparison table containing physical properties, gravity, and escape velocity.

### Exit

Choose option `9` to exit the application. The dynamically allocated planetary database is released before the program terminates.

---

## 📁 Project Structure

A simple repository layout for the project is:

```text
Space-Mission-Calculator/
│
├── main.c
├── README.md
└── .gitignore
```

- `main.c` — C source code containing the planetary database, calculation functions, menu system, and program entry point.
- `README.md` — project documentation, setup instructions, formulas, and usage guide.
- `.gitignore` — optional file for excluding generated executables and other unnecessary files from version control.

Adjust the filenames in this example to match your actual repository.

---

## 🔢 Sample Calculations

The following are approximate illustrative results using standard Earth parameters and the formulas implemented in the program.

| Calculation | Approximate result |
|---|---:|
| Earth's surface gravity | 9.82 m/s² |
| Earth's escape velocity | 11.19 km/s |
| Weight of a 70 kg person on Earth | 687 N |

For example, the weight of a 70 kg person on Earth is approximately:

\[
W = 70 \times 9.82 \approx 687.4\ \text{N}
\]

Actual displayed values may differ slightly because of the constants and approximate planetary data stored in the source code.

---

## ⚠️ Assumptions and Limitations

This application is designed primarily for learning and demonstration. Its results should not be treated as mission-planning data.

- **Approximate astronomical data:** The planetary database uses embedded values that may differ from current astronomical references.
- **Idealized orbital calculations:** Orbital velocity and period calculations assume circular orbits around the Sun.
- **Simplified travel-time estimates:** The program uses the difference between average heliocentric distances rather than computing actual spacecraft trajectories.
- **Constant spacecraft speed:** The travel-time calculation assumes a constant user-entered speed and does not model acceleration or deceleration.
- **Celestial-body modelling:** The Sun and Moon are included in the same database as the planets, but not every calculation is physically meaningful for every entry. In particular, the heliocentric orbital equations should not be interpreted as accurate orbital models for the Sun or Moon.
- **Terminal dependence:** ANSI colours and screen-clearing behaviour depend on the terminal environment.
- **Platform compatibility:** The current delay implementation uses POSIX-specific functionality and may require changes for native Windows compilation.
- **Input validation scope:** The program validates several user inputs, but this does not guarantee that every possible physically invalid calculation or input condition is handled.

These limitations make the project a useful foundation for future improvements in numerical accuracy, input handling, and software portability.

---

## 🔮 Future Improvements

Possible extensions to the project include:

- [ ] Add all eight planets with a more comprehensive astronomical dataset.
- [ ] Improve the Moon's treatment by modelling its orbit around Earth separately from heliocentric planetary orbits.
- [ ] Introduce more accurate interplanetary distance and trajectory calculations.
- [ ] Add escape-velocity and orbital calculations for user-defined celestial bodies.
- [ ] Allow users to enter custom planetary mass and radius values.
- [ ] Improve validation for extreme values and physically invalid cases.
- [ ] Make terminal clearing and progress-bar behaviour portable across Windows, Linux, and macOS.
- [ ] Separate the source code into multiple `.c` and `.h` files for better modularity.
- [ ] Add automated tests for mathematical calculations.
- [ ] Support exporting calculation results to a text or CSV file.
- [ ] Add a graphical user interface for a more visual experience.

These are potential enhancements rather than features currently implemented.

---

## 📚 Learning Outcomes

Developing this project provides practical experience in:

1. Translating physics equations into executable C code.
2. Organizing related data with structures.
3. Using pointers and dynamically allocated memory.
4. Designing modular programs through reusable functions.
5. Building interactive menu-driven applications.
6. Validating user input and handling common input errors.
7. Applying mathematical functions and unit conversions.
8. Improving readability through formatted terminal output.
9. Recognizing the assumptions and limitations of simplified mathematical models.

The project connects programming fundamentals with a scientific application, demonstrating how software can be used to explore and calculate physical quantities.

---

## 👨‍💻 Author

**Snehankur Mondal**

This project is part of my ongoing learning journey in programming, computational problem-solving, and applying scientific concepts through software development.

### Connect

- **GitHub:** [mondalsnehankur](https://github.com/mondalsnehankur)

---

## ⭐ Support

If you find this project useful for learning C programming or exploring basic planetary physics, consider giving the repository a ⭐ on GitHub.

Feedback, suggestions, and ideas for future improvements are welcome.

---

*Disclaimer: This project is intended for educational purposes. Its simplified calculations and approximate data are not suitable for actual spacecraft navigation, engineering decisions, or mission planning.*
