#ifndef INTERVAL_HPP
#define INTERVAL_HPP
#include "Utility/Helper.hpp"

class Interval
{
public:
    Interval() : m_min( +Infinity ), m_max( -Infinity ) {}
    Interval( double min, double max ) : m_min( min ), m_max( max ) {}

    double Size() const { return m_max - m_min; }
    bool Contains( double x ) const { return x >= m_min && x <= m_max; }
    bool Surrounds( double x ) const { return x > m_min && x < m_max; }

    double m_min;
    double m_max;

    static const Interval Empty;
    static const Interval Universe;
};

#endif