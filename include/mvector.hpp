#ifndef MATH_MVECTOR_HPP
#define MATH_MVECTOR_HPP

#include <initializer_list>
#include <stdexcept>
#include <ostream>

/**
 *  Represents a vector in  the mathematical sense of the word
 *  which implements useful operators for linear algebra operations
 */
class MVector
{
    public:
    /// Constructs vector of size @param size with 0 in all elements
    MVector(unsigned int size);
    MVector(std::initializer_list<double> list);
    ~MVector();
    MVector(const MVector& source);
    MVector& operator=(const MVector& source);
    MVector(MVector&& source);
    MVector& operator=(MVector&& source);

    /// @return same vector
    MVector operator+();
    /// @return sum of two vectors
    MVector operator+(MVector& other);
    /// @return vector with same magnitudes but opposite sign
    MVector operator-();
    /// @return vector which is this - other elements
    MVector operator-(MVector& other);
    /// @return Dot product of two vectors
    MVector operator*(MVector& other);
    /** @return Cross product of two vectors
     *  @throw std::invalid_argument if either this or other is not size 3
     */
    MVector operator%(MVector& other);

    /// @return vector multiplied by @param multiplier
    MVector operator*(double multiplier);
    /// @return vector divided by @param divider
    MVector operator/(double divider);

    /** @return access to number at index @param n
     *  @throw std::out_of_bounds
     */
    double& operator[](const unsigned int n);

    /// @return norm of vector
    double norm();

    /// @return size of the vector
    unsigned int size();

    private:
    unsigned int _size;
    double* data;

    /// Used internally to initialize with a size with 0s or not
    MVector(unsigned int size, bool initializeZeros);
};

/// @return vector @param v multiplied by @param multiplier
MVector operator*(double multiplier, MVector& v);
/// @return @param divided divided by vector @param v
MVector operator/(double divider, MVector& v);

std::ostream &operator<<(std::ostream &os, MVector &v);

#endif