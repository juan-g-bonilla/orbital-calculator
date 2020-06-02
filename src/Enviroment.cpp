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

Propagator* Enviroment::getPropagator()
{
    return propagator.get();
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

void Enviroment::setPropagator(std::unique_ptr<Propagator>&& propagator)
{
    this->propagator = std::move(propagator);
}

// Current implementation can handle up to J3 oblateness
MVector Enviroment::getAcceleration(EphemerisEntry entry)
{
    MVector rv = {entry.getX(), entry.getY(), entry.getZ()};
    double r = rv.norm();
    MVector rdd = -centralBody.getGravitationalParameter()/std::pow(r,3)*rv;

    if (centralBody.isJefferyConstantSet(2))
    {
        double J2 = centralBody.getJefferyConstant(2);
        rdd[0] += J2*rdd[0]/std::pow(r,7)*(6*std::pow(rv[2],2) - 1.5*(std::pow(rv[0],2) + std::pow(rv[1],2)));
        rdd[1] += J2*rdd[1]/std::pow(r,7)*(6*std::pow(rv[2],2) - 1.5*(std::pow(rv[0],2) + std::pow(rv[1],2)));
        rdd[2] += J2*rdd[2]/std::pow(r,7)*(3*std::pow(rv[2],2) - 4.5*(std::pow(rv[0],2) + std::pow(rv[1],2)));
    }

    if (centralBody.isJefferyConstantSet(3))
    {
        double J3 = centralBody.getJefferyConstant(3);
        rdd[0] += J3*rdd[0]*rdd[2]/std::pow(r,9)*(10*std::pow(rv[2],2) - 7.5*(std::pow(rv[0],2) + std::pow(rv[1],2)));
        rdd[1] += J3*rdd[1]*rdd[2]/std::pow(r,9)*(10*std::pow(rv[2],2) - 7.5*(std::pow(rv[0],2) + std::pow(rv[1],2)));
        rdd[2] += J3/std::pow(r,9)*(4*std::pow(rdd[2],2)*(std::pow(rdd[2],2) - 3*(std::pow(rv[0],2) + std::pow(rv[1],2)) ) 
                                    + 1.5*std::pow( (std::pow(rv[0],2) + std::pow(rv[1],2)) ,2) );
    }

    return rdd;
}

int Enviroment::propagate()
{
    return propagator->propagate(*this);
}