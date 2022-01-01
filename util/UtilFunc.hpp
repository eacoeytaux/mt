#ifndef utilfunc_hpp
#define utilfunc_hpp

#include "SysIncludes.hpp"
#include "Assert.hpp"

namespace mt {
namespace util {

#define PIXEL_PRECISION_DEPTH 16
#define PIXEL_PRECISION 1/(2<<PIXEL_PRECISION_DEPTH)

// avoid confusion between std::vector and mt::Vector
#define varray std::vector

// allows for for optional params
#define for_range_selector(x,r,i,func,...) func
#define for_range_i(r)   for (int i = 0; i < r; ++i)
#define for_range_x(i,r) for (int i = 0; i < r; ++i)
#define for_range(...)   for_range_selector(,##__VA_ARGS__,for_range_x(__VA_ARGS__),for_range_i(__VA_ARGS__))

#define for_each(x,list) for (auto x : list)

const float DEFAULT_FLOAT_EPSILON = PIXEL_PRECISION;

/// @brief float equal
/// @param x first float
/// @param y second float
/// @param epsilon (optional) how close the floats can be to considered equal
/// @return true if floats are close enough in value
inline bool float_eq(float x, float y, float epsilon = DEFAULT_FLOAT_EPSILON) {
    if(fabs(x - y) < epsilon) return true; // equals!
    else return false;
}

/// @brief float greater than
/// @param x first float
/// @param y second float
/// @param epsilon (optional) how close the floats can be to considered equal
inline bool float_gt(float x, float y, float epsilon = DEFAULT_FLOAT_EPSILON) {
    return (x > y);
}

/// @brief float greater than or equal
/// @param x first float
/// @param y second float
/// @param epsilon (optional) how close the floats can be to considered equal
inline bool float_ge(float x, float y, float epsilon = DEFAULT_FLOAT_EPSILON) {
    return ((x > y) || float_eq(x, y));
}

/// @brief float less than
/// @param x first float
/// @param y second float
/// @param epsilon (optional) how close the floats can be to considered equal
inline bool float_lt(float x, float y, float epsilon = DEFAULT_FLOAT_EPSILON) {
    return (x < y);
}

/// @brief float less than or equal
/// @param x first float
/// @param y second float
/// @param epsilon (optional) how close the floats can be to considered equal
inline bool float_le(float x, float y, float epsilon = DEFAULT_FLOAT_EPSILON) {
    return ((x < y) || float_eq(x, y));
}

/// @brief turns variable to negative
/// @param t variable to flip
template<typename T>
void flip(T & t) {
    t *= -1;
}

/// @brief turns variable to negative
/// @param t variable to flip
/// @return flipped variable
template<typename T>
T flip(const T & t) {
    return t * -1;
}

/// @brief swaps two variables
/// @param t1 first variable
/// @param t2 second variable
template<typename T>
void swap(T & t1, T & t2) {
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

/// @brief returns whether a variable is in range
/// @param t first variable
/// @param high upper bound of range
/// @param low lower bound of range, default 0
/// @param inclusive returns true if ( t == high ) || ( t == low )
/// @return whether variable is in range
template<typename T>
bool in_range(const T & t, const T & high, const T & low = T(0), bool inclusive = true) {
    T h = high;
    T l = low;
    if (l > h) swap<T>(h, l);
    return (inclusive && ((t >= l) && (t <= h))) || (!inclusive && ((t > l) && (t < h)));
}

/// @brief returns absolute value of variable
/// @param t variable to take absolute value
/// @return absolute value of variable
template<typename T>
T abs(const T & t) {
    if (t < 0) return t * -1;
    else return t;
}

/// @brief to the power!
/// @param t base value
/// @param p exponent value
/// @return t^p
template<typename T>
T pow(const T & t, const unsigned int p) {
    if (!p) return T();
    T ret = t;
    for_range (p - 1) {
        ret *= t;
    }
    return ret;
}

/// @brief minimum of two values
/// @param t1 first value
/// @param t2 second value
/// @return minimum value
template<typename T>
T min(const T & t1, const T & t2) {
    if (t1 <= t2) {
        return t1;
    } else {
        return t2;
    }
}

/// @brief minimum value from list
/// @param list list of values
/// @return minimum value in list
template<typename T>
T min(const varray<T> & list) {
    Assert::soft(list.size(), "list must not be empty");
    T ret = list[0];
    for_each (t, list) if (t < ret) ret = t;
    return ret;
}

/// @brief maximum of two values
/// @param t1 first value
/// @param t2 second value
/// @return maximum value
template<typename T>
T max(const T & t1, const T & t2) {
    if (t1 >= t2) {
        return t1;
    } else {
        return t2;
    }
}

/// @brief maximum value from list
/// @param list list of values
/// @return maximum value in list
template<typename T>
T max(const varray<T> & list) {
    Assert::soft(list.size(), "list must not be empty");
    T ret = list[0];
    for_each (t, list) {
        if (t > ret) ret = t;
    }
    return ret;
}

}
}

#endif /* utilfunc_hpp */
