#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <vector>

/**
 * Represents a celestial body (planet, asteroid...) that can exert gravitational influence on another body.
 */
class CelestialBody
{
    public:
    ///Sets Standard Gravitational Parameter of body in km^3/s^2
    void setGravitationalParameter(double mu);

    /** Set Jeffery constant @param n in units of km^(n+3)*s^−2
     *  @throw std::invalid_argument if the previous Jeffery constant has not been set.
     *  The Jeffery constant 1 is ignored, so setting the constant 2 first will not throw
     *  an exception.
     */
    void setJefferyConstant(unsigned int n, double constant);

    /// @return Standard Gravitational Parameter of body in km^3/s^2
    double getGravitationalParameter() const;

    /** @return the @param n Jeffery constant in units of km^(n+3)*s^−2
     *  @throw std::out_of_range if the constant has not been set yet
     */
    double getJefferyConstant(unsigned int n) const;
    
    /// @return true iff the n constant has been set
    bool isJefferyConstantSet(unsigned int n) const;

    private:
    double mu{0}; // Gravitational constant (km^3/s^2)
    std::vector<double> J; // Jeffery's constants in units of km^(n+3)*s^−2
};

#endif