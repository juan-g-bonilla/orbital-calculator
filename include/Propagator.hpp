#include "Enviroment.hpp"

class Propagator
{
    public:
    /** Resets the ephemeris and propagates it in the given enviroment
     *  @return 0 if no error happened during computation
     */  
    virtual int propagate(Enviroment& enviroment) = 0;
};

/** Uses the Leapfrog integration method to propagate the orbit.
 *  This method can be used for n-body problems since the acceleration
 *  depends exclusively on the position of the particle.
 *  See: "http://www.artcompsci.org/vol_1/v1_web/node34.html"
 */
class LeapfrogPropagator : public Propagator
{
    /** Resets the ephemeris and propagates it in the given enviroment
     *  @return 0 if no error happened during computation
     *  @return 1 if there is no initial EphemerisEntry
     *  @return 2 if centralBody still has default parameter == 0
     *  @return 3 if final time and time set are set so that t0 >= (tf - dt)
     */ 
    int propagate(Enviroment& enviroment) override;
};