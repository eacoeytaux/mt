#ifndef sysincludes_hpp
#define sysincludes_hpp

#include "Debug.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

namespace mt {

// general
using std::shared_ptr;
using std::string;

// math
using std::sqrt;
using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;
using std::atan2;

const float PI = M_PI; // 3.141592653589793238463
const float POS_INFINITY = std::numeric_limits<float>::max();
const float NEG_INFINITY = std::numeric_limits<float>::min();

using std::cout;
using std::endl;

}

#endif /* sysincludes_hpp */