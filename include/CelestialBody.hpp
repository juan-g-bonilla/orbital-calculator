#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

/**
 * Represents a celestial body (planet, asteroid...) that can exert gravitational influence on another body.
 */
class CelestialBody
{
    public:
    CelestialBody(double mu) : mu(mu) {};

    /// @return Standard Gravitational Parameter of body in km^3/s^2
    double getGravitationalParameter();
    
    private:
    double mu; // Gravitational constant (km^3/s^2)
};

#endif