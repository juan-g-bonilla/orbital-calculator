#include "mvector.hpp"
#include <cmath>

using std::pow;

MVector::MVector(unsigned int __size, bool _initialize)
{
    if (__size == 0)
        throw std::invalid_argument("Size must be greater than 0");

    _size = __size;

    if (_initialize)
        data = new double[_size] {};
    else
        data = new double[_size];
}

MVector::MVector(unsigned int _size) : MVector(_size, true) {};

MVector::MVector(std::initializer_list<double> list)
{
    _size = list.size();

    if (_size == 0)
        throw std::invalid_argument("Size must be greater than 0");

    data = new double[_size];

    for (int i = 0; i < _size; i++)
        data[i] = *(list.begin() + i);
}

MVector::~MVector()
{
    delete[] data;
}

MVector::MVector(const MVector& source)
{
    _size = source._size;
    data = new double[_size];

    for (int i = 0; i < _size; i++)
        data[i] = source.data[i];
}

MVector& MVector::operator=(const MVector& source)
{
    if (this == &source)
            return *this;
    delete[] data;

    _size = source._size;
    data = new double[_size];

    for (int i = 0; i < _size; i++)
        data[i] = source.data[i];

    return *this;
}

MVector::MVector(MVector&& source)
{
    _size = source._size;
    data = source.data;
    source.data = nullptr;
}

MVector& MVector::operator=(MVector&& source)
{
    if (this == &source)
            return *this;
    delete[] data;

    _size = source._size;
    data = source.data;
    source.data = nullptr;
    return *this;
}

MVector MVector::operator+() const
{
    return *this;
}

MVector MVector::operator+(const MVector& other) const
{
    if (_size != other._size)
        throw std::invalid_argument("Vector size must coincide");

    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = (*this)[i] + other[i];
    
    return std::move(result);
}

MVector MVector::operator-() const
{
    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = -(*this)[i];
    
    return std::move(result);
}

MVector MVector::operator-(const MVector& other) const
{
    if (_size != other._size)
        throw std::invalid_argument("Vector size must coincide");

    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = (*this)[i] - other[i];
    
    return std::move(result);
}

MVector MVector::operator*(const MVector& other) const
{
    if (_size != other._size)
        throw std::invalid_argument("Vector size must coincide");

    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = (*this)[i] * other[i];
    
    return std::move(result);
}

MVector MVector::operator%(const MVector& other) const
{
    if (_size != other._size || _size != 3)
        throw std::invalid_argument("Vectors size must be 3");

    MVector result(3, false);
    result[0] = (*this)[1]*other[2] - (*this)[2]*other[1];
    result[1] = (*this)[2]*other[0] - (*this)[0]*other[2];
    result[2] = (*this)[0]*other[1] - (*this)[1]*other[0];

    return std::move(result);
}

MVector MVector::operator*(double multiplier) const
{
    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = (*this)[i] * multiplier;
    return std::move(result);
}

MVector MVector::operator/(double divider) const
{
    MVector result(_size, false);
    for (int i = 0; i < _size; i++)
        result[i] = (*this)[i] / divider;
    return std::move(result);
}

bool MVector::operator==(const MVector& other) const
{
    if (this->_size != other._size) return false;

    for (int i = 0; i < _size; i++)
        if ((*this)[i] != other[i]) return false;

    return true;
}

double& MVector::operator[](const unsigned int n) const
{
    return data[n];
}

double MVector::norm() const
{
    double result;
    for (int i = 0; i < _size; i++)
    {
        result += pow(data[i],2);
    }
    return pow(result, 0.5);
}

unsigned int MVector::size() const
{
    return _size;
}

MVector operator*(double multiplier, const MVector& v)
{
    return std::move(v*multiplier);
}

MVector operator/(double divided, const MVector& v)
{
    MVector result(v.size());
    for (int i = 0; i < v.size(); i++)
        result[i] = divided / v[i];
    return std::move(result);
}

std::ostream &operator<<(std::ostream &os, const MVector &v)
{ 
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
        if (i != v.size() -1)
            os << ",";
    }

    return os;
}