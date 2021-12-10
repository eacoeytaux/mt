#ifndef Slider_hpp
#define Slider_hpp

#include "mt.hpp"

namespace mt {

template<typename T>
class Slider {
public:
    Slider(const T & max = T(0)) :
    m_max(max) {
        value(0);
    }
    
    T max() const {
        return m_max;
    }
    
    T value() const {
        return m_value;
    }
    
    void value(const T & value) {
        assert((value <= m_max) && (value >= 0));
        m_value = value;
    }
    
    float percentage() const {
        return (float)m_value / (float)m_max;
    }
    
    void percentage(const float percentage) {
        Assert::soft((percentage <= 1) && (percentage >= 0), "percentage (%f) should not be outside bounds [0,0]", percentage);
        m_value = ((m_max - m_min) * percentage) + m_min;
    }
    
private:
    T m_value;
    T m_max;
    T m_min;
};

}

#endif /* Slider_hpp */
