#ifndef ENVIROMENT_HPP
#define ENVIROMENT_HPP

#include "CelestialBody.hpp"
#include "Ephemeris.hpp"
#include "MVector.hpp"

class Enviroment
{
    public:
    Enviroment() {};
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
    void setTimeStep(double time);

    /** Get the acceleration the orbiting body suffers in the position
     *  defined by @param currentPosition, in km/s^2 and stored in a 
     *  3 size vector
     */
    MVector getAcceleration(EphemerisEntry currentPosition);

    private:
    CelestialBody centralBody{0};
    Ephemeris ephemeris{};
    double tf{0}, dt{0};
};

#endif