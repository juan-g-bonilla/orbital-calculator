#include "Enviroment.hpp"
#include <stdexcept>
#include <cmath>

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

EphemerisEntryBuilder& Enviroment::getEphemerisEntryBuilder()
{
    return builder;
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

void Enviroment::setTimeStep(double time)
{
    if (time <= 0)
        throw std::invalid_argument("Time step must be higher than 0");

    dt = time;
}

// Current implementation is two-body
MVector Enviroment::getAcceleration(EphemerisEntry entry)
{
    MVector r = {entry.getX(), entry.getY(), entry.getZ()};
    return -centralBody.getGravitationalParameter()/std::pow(r.norm(),3)*r;
}