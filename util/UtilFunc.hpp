#ifndef utilfunc_hpp
#define utilfunc_hpp

#include "SysIncludes.hpp"

namespace mt {

#define pixel_precision_depth 16
#define pixel_precision 1/(2<<pixel_precision_depth)

// avoid confusion between std::vector and mt::Vector
#define varray std::vector

// allows for for optional params
#define for_range_selector(x,r,i,func,...) func
#define for_range_i(r)   for (int i = 0; i < r; ++i)
#define for_range_x(i,r) for (int i = 0; i < r; ++i)
#define for_range(...)   for_range_selector(,##__VA_ARGS__,for_range_x(__VA_ARGS__),for_range_i(__VA_ARGS__))

#define for_each(x,list) for (auto x : list)

#define va_list_from_char(STR) va_list args; va_start(args,STR);

const float __default_float_epsilon = 0.01;

inline bool float_eq(float x, float y, float epsilon = __default_float_epsilon) {
    if(fabs(x - y) < epsilon) return true; // equals!
    else return false;
}

inline bool float_gt(float x, float y, float epsilon = __default_float_epsilon) {
    return (x > y);
}

inline bool float_ge(float x, float y, float epsilon = __default_float_epsilon) {
    return ((x > y) || float_eq(x, y));
}

inline bool float_lt(float x, float y, float epsilon = __default_float_epsilon) {
    return (x < y);
}

inline bool float_le(float x, float y, float epsilon = __default_float_epsilon) {
    return ((x < y) || float_eq(x, y));
}

template<typename T>
void flip(T & t) {
    t *= -1;
}

template<typename T>
T flip(const T & _t) {
    return _t * -1;
}

template<typename T>
varray<T> populate_varray(const T & _t, const unsigned int _count) {
    varray<T> ret(_count);
    for_range(_count) ret[i] = _t;
    return ret;
}

template<typename T>
void swap(T & t1, T & t2) {
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

template<typename T>
bool in_range(const T & _t, const T & _high, const T & _low = T(0), bool _inclusive = true) {
    T high = _high;
    T low = _low;
    if (low < high) swap<T>(high, low);
    return (_inclusive && ((_t >= low) && (_t <= high))) || (!_inclusive && ((_t > low) && (_t < high)));
}

template<typename T>
T abs(const T & t) {
    if (t < 0) return t * -1;
    else return t;
}

template<typename T>
T pow(const T & _t, const unsigned int _p) {
    if (!_p) return T();
    T ret = _t;
    for_range (_p - 1) {
        ret *= _t;
    }
    return ret;
}

template<typename T>
T min(const T & _t1, const T & _t2) {
    if (_t1 <= _t2) {
        return _t1;
    } else {
        return _t2;
    }
}

template<typename T>
T min(const varray<T> & _list) {
    assert(_list.size());
    T ret = _list[0];
    for_each (t, _list) {
        if (t < ret) ret = t;
    }
    return ret;
}

template<typename T>
T max(const T & _t1, const T & _t2) {
    if (_t1 >= _t2) {
        return _t1;
    } else {
        return _t2;
    }
}

template<typename T>
T max(const varray<T> & _list) {
    assert(_list.size());
    T ret = _list[0];
    for_each (t, _list) {
        if (t > ret) ret = t;
    }
    return ret;
}

}

#endif /* utilfunc_hpp */
