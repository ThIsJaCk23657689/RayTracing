#include "Utility/Interval.hpp"

const Interval Interval::Empty    = Interval(+Infinity, -Infinity);
const Interval Interval::Universe = Interval(-Infinity, +Infinity);