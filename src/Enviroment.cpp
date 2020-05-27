#include "Enviroment.hpp"

CelestialBody& Enviroment::getCentralBody()
{
    return centralBody;
}

Ephemeris& Enviroment::getEphemeris()
{
    return ephemeris;
}

void Enviroment::setCentralBody(CelestialBody central)
{
    centralBody = central;
}

void Enviroment::setEphemeris(Ephemeris ephemeris)
{
    this->ephemeris = std::move(ephemeris);
}