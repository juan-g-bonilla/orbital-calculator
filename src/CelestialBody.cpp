#include "CelestialBody.hpp"
#include <stdexcept>

CelestialBody::CelestialBody(double mu)
{
    if (mu < 0)
        throw std::invalid_argument("The gravitational parameter cannot be negative");

    this->mu = mu;
}

double CelestialBody::getGravitationalParameter() const
{
    return mu;
}