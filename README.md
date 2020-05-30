# Orbital Calculator

Calculator for propagating orbits of bodies around a central body following two-body physics.
The results obtainable from this program are a propagated Ephemeris (position and velocity) of
an orbiting body given initial conditions. This results can be looked up at a specific instant of time
or output completely to a file of further calculations.

## Usage 
You can use the command "help" to see all available commands and obtain information about them.
A simple use case involves setting the initial coordinates of the body with the command ("initial coord"),
setting the gravitational parameter of the central body ("central grav"), how many seconds we want to compute
("env tf") and the time step ("env dt"). Then propagate using ("propagate"). 
To look up the results at a specific time use ("results at"). To output the results to a file use ("results to file").

Example:
```
initial coord 9222.33 1408.28 813.073 -1.291 6.344 3.663
central grav 398601
env tf 100
env dt 0.5
propagate
results at 62.5
results to file "example.txt"
```

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./OrbitalCalculator`.

## File and class structure
* ConsoleHandler stores an Enviroment variable and handles user input; command declaration and execution; 
and console and file output. 
* Enviroment class stores the enviroment central CelestialBody, orbiting body's 
Ephemeris, a Propagator for the Ephemeris, an EphemerisEntryBuilder to aid the creation of the first entry 
of Ephemeris (which is user defined) and the time step and final time of the propagation.
* Celestial Body represents a celestial body (planet, asteroid...) that can exert gravitational influence on another body.
* Ephemeris stores a chronological collection of EphemerisEntry (which stores x, y, z coordinates of position and velocity). 
* EphemerisEntryBuilder allows defining the initial entry of the Ephemeris (ie the initial position of orbiting body).
* Additionally, there is a util math class MVector which represents a vector in  the mathematical sense of the word which 
implements useful operators for linear algebra operations

## Requirements met
* The project reads data from a file and process the data, or the program writes data to a file: ConsoleHandler.cpp::251
* The project accepts user input and processes the input: ConsoleHandler.cpp::309
* Class constructors utilize member initialization lists: Ephemeris.hpp::75
* Classes abstract implementation details from their interfaces: MVector.hpp
* Classes follow an appropriate inheritance hierarchy: Propagator.hpp
* Derived class functions override virtual base class functions: Propagator.hpp::34
* The project uses destructors appropriately: MVector.cpp::36
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: MVector.cpp::6
* The project follows the Rule of 5: MVector.hpp::18
* The project uses smart pointers instead of raw pointers: Enviroment.hpp::51