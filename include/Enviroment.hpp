#ifndef ENVIROMENT_HPP
#define ENVIROMENT_HPP

#include "CelestialBody.hpp"
#include "Ephemeris.hpp"

class Enviroment
{
    CelestialBody& getCentralBody();
    Ephemeris& getEphemeris();

    void setCentralBody(CelestialBody central);
    void setEphemeris(Ephemeris ephemeris);

    private:
    CelestialBody centralBody;
    Ephemeris ephemeris;
};

#endif