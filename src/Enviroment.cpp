#include "Enviroment.hpp"
#include <stdexcept>

CelestialBody& Enviroment::getCentralBody()
{
    return centralBody;
}

Ephemeris& Enviroment::getEphemeris()
{
    return ephemeris;
}

double Enviroment::getFinalTime()
{
    return tf;
}

double Enviroment::getTimeStep()
{
    return dt;
}

void Enviroment::setCentralBody(CelestialBody central)
{
    centralBody = central;
}

void Enviroment::setEphemeris(Ephemeris ephemeris)
{
    this->ephemeris = std::move(ephemeris);
}

void Enviroment::setFinalTime(double time)
{
    if (time <= 0)
        throw std::invalid_argument("Final time must be higher than 0");

    tf = time;
}

void Enviroment::setFinalTime(double time)
{
    if (time <= 0)
        throw std::invalid_argument("Time step must be higher than 0");

    dt = time;
}