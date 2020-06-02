#include "CelestialBody.hpp"
#include <stdexcept>

double CelestialBody::getJefferyConstant(unsigned int n) const
{
    return J[n-2];
}

bool CelestialBody::isJefferyConstantSet(unsigned int n) const
{
    return n - 2  < J.size();
}

double CelestialBody::getGravitationalParameter() const
{
    return mu;
}

void CelestialBody::setGravitationalParameter(double mu)
{
    if (mu < 0)
        throw std::invalid_argument("The gravitational parameter cannot be negative");

    this->mu = mu;
}

void CelestialBody::setJefferyConstant(unsigned int n, double constant)
{
    if (n - 2  > J.size())
        throw std::invalid_argument("The previous Jeffery constant has not been set");
    
    else if (n-2 == J.size())
    {
        J.push_back(constant);
    } 
    else
    {
        J[n-2] = constant;
    }
}