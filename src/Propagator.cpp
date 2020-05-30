#include "Propagator.hpp"
#include "Enviroment.hpp"
#include "MVector.hpp"
#include <cmath>
#include <iostream>

using std::pow;

std::string Propagator::getExitMessage(int i)
{
    switch(i)
    {
        case 0: return "Propagation succesful";
    }
}

int LeapfrogPropagator::propagate(Enviroment& env)
{
    if (env.getCentralBody().getGravitationalParameter() == 0) return 2;

    Ephemeris& eph = env.getEphemeris();

    if (eph.empty()) return 1;
    
    eph.reset();

    double t{eph.at(0).getTime()}, tf{env.getFinalTime()}, dt{env.getTimeStep()};

    if (t >= tf - dt) return 3;

    int i = 0;

    MVector xi = {eph.at(0).getX(), eph.at(0).getY(), eph.at(0).getZ()};
    MVector vi = {eph.at(0).getVx(), eph.at(0).getVy(), eph.at(0).getVz()};
    MVector ai = env.getAcceleration(eph.at(0));

    while (t < tf - dt)
    {
        /*
        std::cout << "i= " << i << std::endl;
        std::cout << "  " << xi << std::endl;
        std::cout << "  " << vi << std::endl;
        std::cout << "  " << ai << std::endl;
        */
        t += dt;
        xi = xi + vi*dt + ai*pow(dt,2)/2;
        MVector aiplus1 = env.getAcceleration({xi[0], xi[1], xi[2], 0,0,0,t});
        vi = vi + (ai + aiplus1)*dt/2;
        ai = std::move(aiplus1);
        eph.include({xi[0], xi[1], xi[2], vi[0], vi[1], vi[2],t});
        i++;
    }

    return 0;
}

std::string LeapfrogPropagator::getExitMessage(int i)
{
    switch(i)
    {
        case 0: return "Propagation succesful";
        case 1: return "No initial position has been set";
        case 2: return "Central body has not been defined";
        case 3: return "Final time or time step have not been set";
    }
}