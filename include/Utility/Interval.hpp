#ifndef INTERVAL_HPP
#define INTERVAL_HPP
#include "Utility/Helper.hpp"

template< typename T >
struct Interval {
    Interval() : m_min( +Infinity ), m_max( -Infinity ) {}
    Interval( T min, T max ) : m_min( min ), m_max( max ) {}

    T Size() const { return m_max - m_min; }
    T Clamp( T x ) const { return clamp(x, m_min, m_max); }
    bool Contains( T x ) const { return x >= m_min && x <= m_max; }
    bool Surrounds( T x ) const { return x > m_min && x < m_max; }

    T m_min;
    T m_max;

    static const Interval< T > Empty;
    static const Interval< T > Universe;

    static const T Infinity;
};

template<typename T>
const T Interval<T>::Infinity = std::numeric_limits<T>::infinity();

template<typename T>
const Interval<T> Interval<T>::Empty = Interval<T>(+Infinity, -Infinity);

template<typename T>
const Interval<T> Interval<T>::Universe = Interval<T>(-Infinity, +Infinity);
#endif