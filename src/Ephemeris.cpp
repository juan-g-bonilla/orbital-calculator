#include "Ephemeris.hpp"
#include <stdexcept>
#include <cmath>
#include "MVector.hpp"

#define M_PI 3.14159265358979323846  /* pi */

using std::pow;
using std::cos;
using std::sin;

/* Ephemeris Class */

Ephemeris::Ephemeris(const Ephemeris &source)
{
    this->entries = source.entries;
}

Ephemeris& Ephemeris::operator=(const Ephemeris& source)
{
    if (this == &source)
            return *this;
    this->entries = source.entries;

    return *this;
}

Ephemeris::Ephemeris(Ephemeris&& source)
{
    this->entries = std::move(source.entries);
}

Ephemeris& Ephemeris::operator=(Ephemeris&& source)
{
    if (this == &source)
            return *this;
    this->entries = std::move(source.entries);

    return *this;
}

size_t Ephemeris::size()
{
    return entries.size();
}

EphemerisEntry&  Ephemeris::at(size_t n)
{
    return entries.at(n);
}

EphemerisEntry& Ephemeris::when(double t)
{
    if (t < entries.at(0).getTime()) return entries.at(0);

    for (int i = 0; i < entries.size(); i++)
    {
        if (entries.at(i).getTime() > t)
        {
            if (i == entries.size()-1) return entries.at(i);

            if (t - entries.at(i).getTime() > entries.at(i+1).getTime() - t)
            {
                return entries.at(i+1);
            }
            else
            {
                return entries.at(i);
            }
        }
    }
}

bool Ephemeris::empty()
{
    return entries.empty();
}

size_t Ephemeris::include(EphemerisEntry entry)
{
    if (empty())
    {
        entries.push_back(entry);
        return 0;
    }

    /// Most common use-case scenario, thus checked first
    if (entries.back().getTime() < entry.getTime())
    {
        entries.push_back(entry);
        return entries.size() - 1;
    }

    if (entry.getTime() < entries.at(0).getTime())
    {
        entries.insert(entries.begin(), entry);
        return 0;
    }

    for (int i = 0; i < entries.size() -1; i++)
    {
        if (entry.getTime() > entries.at(i).getTime())
        {
            entries.insert(entries.begin() + i, entry);
            return i+1;
        }
    }
}

void Ephemeris::setInitialEntry(EphemerisEntry entry)
{
    entries.clear();
    entries.push_back(entry);
}

void Ephemeris::reset()
{
    if (empty()) return;

    EphemerisEntry initial = entries.at(0);
    setInitialEntry(initial);
}

std::ostream& Ephemeris::output(std::ostream &os, bool verbose)
{
    for (auto ent : entries)
    {
        ent.output(os, verbose) << std::endl;
    }

    return os;
}

void Ephemeris::clear()
{
    entries.clear();
}

/* EphemerisEntry */

double EphemerisEntry::getX() const { return x;}
double EphemerisEntry::getY() const { return y;}
double EphemerisEntry::getZ() const { return z;}
double EphemerisEntry::getVx() const { return vx;}
double EphemerisEntry::getVy() const { return vy;}
double EphemerisEntry::getVz() const { return vz;}
double EphemerisEntry::getTime() const { return t;}

std::ostream& EphemerisEntry::output(std::ostream &os, bool verbose)
{
    if (verbose)
    {
        os << "x: " << getX() << " km" << std::endl;
        os << "y: " << getY() << " km" << std::endl;
        os << "z: " << getZ() << " km" << std::endl;
        os << "vx: " << getVx() << " km/s" << std::endl;
        os << "vy: " << getVy() << " km/s" << std::endl;
        os << "vz: " << getVz() << " km/s" << std::endl;
        os << "t: " << getTime() << " s" << std::endl;
    }
    else
    {
        os << getTime() << "\t" 
        << getX() << "\t" << getY() << "\t" << getZ() << "\t"
        << getVx() << "\t" << getVy() << "\t" << getVz();
    }

    return os;
}

/* EphemerisEntryBuilder */

EphemerisEntryBuilder::EphemerisEntryBuilder(EphemerisEntry _e, CelestialBody _b) :
x(_e.getX()), y(_e.getY()), z(_e.getZ()), vx(_e.getVx()), vy(_e.getVy()), vz(_e.getVz()), 
t(_e.getTime()), referenceBody(_b)
{
    MVector r{_e.getX(), _e.getY(), _e.getZ()}, v{_e.getVx(), _e.getVy(), _e.getVz()};
    double mu = _b.getGravitationalParameter();

    // Specific mechanical energy of the orbit
    double energy = pow(v.norm(), 2)/2 - mu / r.norm();

    // Specific angular momentum vector
    MVector h = r%v;

    // Eccentricity vector
    MVector ecc = (v%h) / mu - r / r.norm();

    MVector zAxis = {0, 0, 1};
    // Ascending node vector
    MVector n = zAxis % h;

    a = -mu / 2 / energy;
    e = ecc.norm();
    i = std::acos(h[2] / h.norm());

    lonAscNode = std::acos(n[0] / n.norm());
    if (n[1] < 0) lonAscNode = 2*M_PI - lonAscNode.value();  
    argPeriap = std::acos( ecc*n / n.norm() / ecc.norm() );
    if (ecc[2] < 0) argPeriap = 2*M_PI - argPeriap.value();

    anom = std::acos( ecc*r / r.norm() / ecc.norm() );
    if (r*v < 0) anom = 2*M_PI - anom.value();
}

void EphemerisEntryBuilder::setX(double _x) {settingCartesian = true; x = _x;}
void EphemerisEntryBuilder::setY(double _y) {settingCartesian = true; y = _y;}
void EphemerisEntryBuilder::setZ(double _z) {settingCartesian = true; z = _z;}
void EphemerisEntryBuilder::setVx(double _vx) {settingCartesian = true; vx = _vx;}
void EphemerisEntryBuilder::setVy(double _vy) {settingCartesian = true; vy = _vy;}
void EphemerisEntryBuilder::setVz(double _vz) {settingCartesian = true; vz = _vz;}

void EphemerisEntryBuilder::setA(double _a)
{
    if (_a <= 0)
        throw std::invalid_argument("Semi-major axis must be greater than 0");

    settingCartesian = false;
    a = _a;
}
void EphemerisEntryBuilder::setE(double _e)
{
    if (_e < 0 || _e >= 1)
        throw std::invalid_argument("Eccentricity must be >= 0 and < 1");

    settingCartesian = false;
    e = _e;
}
void EphemerisEntryBuilder::setI(double _i)
{
    if (_i < 0 || _i > 180)
        throw std::invalid_argument("Inclination must be >= 0 degrees and <= 180 degrees");

    settingCartesian = false;
    i = _i/180*M_PI; // angles stored as rad
}
void EphemerisEntryBuilder::setLongitudeAscendingNode(double _l) {settingCartesian = false; lonAscNode = _l/180*M_PI;}
void EphemerisEntryBuilder::setArgumentPerigee(double _arg) {settingCartesian = false; argPeriap = _arg/180*M_PI;}
void EphemerisEntryBuilder::setTrueAnomaly(double _anom) {settingCartesian = false; anom = _anom/180*M_PI;}

void EphemerisEntryBuilder::setTime(double _t)
{
    if (_t < 0)
        throw std::invalid_argument("Reference time must be greater than or equal 0");

    t = _t;
}

bool EphemerisEntryBuilder::isValid()
{
    if (settingCartesian)
    {
        return x && y && z && vx && vy && vz && t;
    }
    else
    {
        return referenceBody && a && e && i && lonAscNode && argPeriap && anom && t;
    }
}

EphemerisEntry EphemerisEntryBuilder::build()
{
    if (!isValid())
        throw std::invalid_argument("Not enough parameters have been set");

    /*
        "To go from COE to state vector, first compute r and v in the perifocal reference frame vector
        basis. Then, transform the matrix to the original reference frame in which the state vector
        should be provided (e.g. ECI-equatorial), by undoing the three rotations associated to the
        Euler angles." Space Vehicles and Orbital Dynamics: Merino, Mario
    */
    if (!settingCartesian)
    {
        double mu = referenceBody.value().getGravitationalParameter();

        x = (a.value()*sin(anom.value())*(pow(e.value(),2) - 1)*
            (cos(lonAscNode.value())*sin(argPeriap.value()) + 
            cos(argPeriap.value())*cos(i.value())*sin(lonAscNode.value())))/(e.value()*cos(anom.value()) + 1)
            - (a.value()*cos(anom.value())*(pow(e.value(),2) - 1)*(cos(argPeriap.value())*cos(lonAscNode.value()) 
            - cos(i.value())*sin(argPeriap.value())*sin(lonAscNode.value())))/(e.value()*cos(anom.value()) + 1);

        y = (a.value()*sin(anom.value())*(pow(e.value(),2) - 1)*(sin(argPeriap.value())*sin(lonAscNode.value()) - 
            cos(argPeriap.value())*cos(i.value())*cos(lonAscNode.value())))/(e.value()*cos(anom.value()) + 1) - 
            (a.value()*cos(anom.value())*(pow(e.value(),2) - 1)*(cos(argPeriap.value())*sin(lonAscNode.value()) 
            + cos(i.value())*cos(lonAscNode.value())*sin(argPeriap.value())))/(e.value()*cos(anom.value()) + 1);

        z = - (a.value()*cos(anom.value())*sin(argPeriap.value())*sin(i.value())*(pow(e.value(),2) - 1))/
            (e.value()*cos(anom.value()) + 1) - (a.value()*cos(argPeriap.value())*sin(anom.value())*sin(i.value())
            *(pow(e.value(),2) - 1))/(e.value()*cos(anom.value()) + 1);

        vx = - (mu*(cos(lonAscNode.value())*sin(argPeriap.value()) + 
            cos(argPeriap.value())*cos(i.value())*sin(lonAscNode.value()))*(e.value() + 
            cos(anom.value())))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5) - 
            (mu*sin(anom.value())*(cos(argPeriap.value())*cos(lonAscNode.value()) - 
            cos(i.value())*sin(argPeriap.value())*sin(lonAscNode.value())))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5);

        vy = - (mu*(sin(argPeriap.value())*sin(lonAscNode.value()) - 
            cos(argPeriap.value())*cos(i.value())*cos(lonAscNode.value()))*(e.value() + 
            cos(anom.value())))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5) - 
            (mu*sin(anom.value())*(cos(argPeriap.value())*sin(lonAscNode.value()) + 
            cos(i.value())*cos(lonAscNode.value())*sin(argPeriap.value())))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5);

        vz = (mu*cos(argPeriap.value())*sin(i.value())*(e.value() + 
             cos(anom.value())))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5) - 
             (mu*sin(anom.value())*sin(argPeriap.value())*sin(i.value()))/pow(-a.value()*mu*(pow(e.value(),2) - 1),0.5);

    }

    return {x.value(), y.value(), z.value(), vx.value(), vy.value(), vz.value(), t.value()};
}

void EphemerisEntryBuilder::output(std::ostream &os)
{
    if (settingCartesian)
    {
        os << "x: ";
        if (x) os << x.value() << " km"; else os << "NaN";
        os << std::endl;

        os << "y: ";
        if (y) os << y.value() << " km"; else os << "NaN";
        os << std::endl;

        os << "z: ";
        if (z) os << z.value() << " km"; else os << "NaN";
        os << std::endl;

        os << "vx: ";
        if (vx) os << vx.value() << " km/s"; else os << "NaN";
        os << std::endl;

        os << "vy: ";
        if (vy) os << vy.value() << " km/s"; else os << "NaN";
        os << std::endl;

        os << "vz: ";
        if (vz) os << vz.value() << " km/s"; else os << "NaN";
        os << std::endl;
    }
    else
    {
        os << "a: ";
        if (a) os << a.value() << " km"; else os << "NaN";
        os << std::endl;

        os << "e: ";
        if (e) os << e.value(); else os << "NaN";
        os << std::endl;

        os << "i: ";
        if (i) os << i.value()*180/M_PI << " degrees"; else os << "NaN";
        os << std::endl;

        os << "Longitude of Ascending Node: ";
        if (lonAscNode) os << lonAscNode.value()*180/M_PI << " degrees"; else os << "NaN";
        os << std::endl;

        os << "Argument Periapsis: ";
        if (argPeriap) os << argPeriap.value()*180/M_PI << " degrees"; else os << "NaN";
        os << std::endl;

        os << "True Anomaly: ";
        if (anom) os << anom.value()*180/M_PI << " degrees"; else os << "NaN";
        os << std::endl;
    }

    os << "Reference Time: ";
    if (t) os << t.value() << " seconds"; else os << "NaN";
    os << std::endl;
}
