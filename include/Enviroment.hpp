#ifndef ENVIROMENT_HPP
#define ENVIROMENT_HPP

#include <memory>

#include "CelestialBody.hpp"
#include "Ephemeris.hpp"
#include "MVector.hpp"
#include "Propagator.hpp"

/** Stores the enviroment central CelestialBody, orbiting body's  Ephemeris, a Propagator 
 * for the Ephemeris, an EphemerisEntryBuilder to aid the creation of the first entry 
 * of Ephemeris (which is user defined) and the time step and final time of the propagation.
 * 
 */
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
    EphemerisEntryBuilder& getEphemerisEntryBuilder();
    /** Using the returned pointer after the method Enviroment::setPropagator
     *  is called or Enviroment goes out of scope will result in a dangling pointer.
     *  Use with care.
     */
    Propagator* getPropagator();

    void setCentralBody(CelestialBody central);
    void setEphemeris(Ephemeris ephemeris);
    /// Sets number of seconds for which we want to propagate orbit
    void setFinalTime(double time);
    /// Sets time step in seconds
    void setTimeStep(double time);
    void setPropagator(std::unique_ptr<Propagator>&& propagator);

    /** Get the acceleration the orbiting body suffers in the position
     *  defined by @param currentPosition, in km/s^2 and stored in a 
     *  3 size vector
     */
    MVector getAcceleration(EphemerisEntry currentPosition);

    /** Propagates the ephemeris of this Enviroment.
     *  @return the exit code of the propagator
     */
    int propagate();

    private:
    CelestialBody centralBody{0};
    Ephemeris ephemeris{};
    EphemerisEntryBuilder builder{};
    std::unique_ptr<Propagator> propagator{new LeapfrogPropagator()};
    double tf{0}, dt{0};
};

#endif