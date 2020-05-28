#ifndef ENVIROMENT_HPP
#define ENVIROMENT_HPP

#include "CelestialBody.hpp"
#include "Ephemeris.hpp"

class Enviroment
{
    CelestialBody& getCentralBody();
    Ephemeris& getEphemeris();
    /// Gets number of seconds for which we want to propagate orbit
    double getFinalTime();
    /// Gets time step in seconds
    double getTimeStep();

    void setCentralBody(CelestialBody central);
    void setEphemeris(Ephemeris ephemeris);
    /// Sets number of seconds for which we want to propagate orbit
    void setFinalTime(double time);
    /// Sets time step in seconds
    void setFinalTime(double time);

    private:
    CelestialBody centralBody;
    Ephemeris ephemeris;
    double tf{0}, dt{0};
};

#endif