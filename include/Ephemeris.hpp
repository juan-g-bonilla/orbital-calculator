#ifndef EPHEMERIS_HPP
#define EPHEMERIS_HPP

#include <vector>
#include <experimental/optional>

using std::vector;
using std::experimental::optional;

class EphemerisEntry;

/**
 * Represents a series of EphemerisEntrys that are in strict temporal order.
 * Implements move semantics.
 */
class Ephemeris
{
    public:
    ~Ephemeris() {};
    Ephemeris(const Ephemeris &source);
    Ephemeris& operator=(const Ephemeris& source);
    Ephemeris(Ephemeris&& source);
    Ephemeris& operator=(Ephemeris&& source);

    /// @return the number of EphemerisEntrys
    size_t size();

    /** @return Read/write reference to entry.
     *  @throw std::out_of_range If @param n is an invalid index.
     */
    EphemerisEntry& at(size_t n);

    /** @return EphemerisEntry that represents a moment in time
     * closest to the given time @param t
     * @throw std::out_of_range If ephemeris is empty
     */
    EphemerisEntry& when(double t);

    /// @return true iff there are no entries
    bool empty();

    /**
     * Inserts the @param entry into the Ephemeris at an appropiate position
     * @return the index of the introduced object
     */ 
    size_t include(EphemerisEntry entry);

    /// Removes all EphemerisEntry and includes this EphemerisEntry
    void setInitialEntry(EphemerisEntry entry);

    /// Removes all EphemerisEntry, except the first EphemerisEntry.
    void reset();

    /// Removes all EphemerisEntry, including the initial position.
    void clear();

    private:
    vector<EphemerisEntry> entries;
};

/**
 * Represents an instant in time where a particle has a certain position (x,y,z) and velocity (vx,vy,vz)
 */
class EphemerisEntry
{
    public:
    EphemerisEntry(double x, double y, double z, double vx, double vy, double vz, double t)
     : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), t(t) {};

    /// @return x-coordinate of position in km
    double getX();
    /// @return y-coordinate of position in km
    double getY();
    /// @return z-coordinate of position in km
    double getZ();
    /// @return x-coordinate of velocity in km/s
    double getVx();
    /// @return y-coordinate of velocity in km/s
    double getVy();
    /// @return z-coordinate of velocity in km/s
    double getVz();
    /// @return reference time in seconds
    double getTime();

    private:
    const double x,y,z,vx,vy,vz,t;
};

class EphemerisEntryBuilder
{
    public:
    EphemerisEntryBuilder() {};
    /// Initializes builder with data from entry
    EphemerisEntryBuilder(EphemerisEntry initialEntry);

    /// Set x-coordinate of position in km
    void setX(double x);
    /// Set y-coordinate of position in km
    void setY(double y);
    /// Set z-coordinate of position in km
    void setZ(double z);
    /// Set x-coordinate of velocity in km/s
    void setVx(double vx);
    /// Set y-coordinate of velocity in km/s
    void setVy(double vy);
    /// Set z-coordinate of velocity in km/s
    void setVz(double vz);

    /// Set semi-major axis in km
    void setA(double a);
    /// Set eccentricity in range [0, 1)
    void setE(double e);
    /// Set inclination in degrees in range [0 180º]
    void setI(double i);
    /// Set Longitude Ascending Node in degrees
    void setLongitudeAscendingNode(double l);
    /// Set Argument of the Perifee in degrees
    void setArgumentPerigee(double arg);
    /// Set True Anomaly in degrees
    void setTrueAnomaly(double anom);

    /// Set reference time in seconds
    void setTime(double t);

    /// @return true iff ephemeris is fully defined 
    bool isValid();

    /**
     * @return EphemerisEntry that corresponds with values set in this builder
     * @throw std::invalid_argument if object is not fully defined
     */
    EphemerisEntry build();

    private:
    optional<double> x,y,z,vx,vy,vz,
                          a,e,i,lonAscNode,argPeriap,anom,
                          t;
    bool settingCartesian {true};
};

#endif