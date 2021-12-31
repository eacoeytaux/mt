#ifndef Slider_hpp
#define Slider_hpp

#include "mt.hpp"

namespace mt {
namespace util {

/// @class Slider
/// @brief slides between two values
template<typename T>
class Slider {
public:
    /// @param max maximum value of slider
    Slider(const T & max = T(0)) :
    m_max(max),
    m_min(0) {
        value(0);
    }
    
    /// @param min minimum value of slider
    /// @param max maximum value of slider
    Slider(const T & min, const T & max) :
    m_max(max),
    m_min(min) {
        value(0);
    }
    
    /// @return maximum value of slider
    T max() const {
        return m_max;
    }
    
    /// @return minimum value of slider
    T minimum() const {
        return m_min;
    }
    
    /// @return current value of slider
    T value() const {
        return m_value;
    }
    
    /// @param value new value of slider
    void value(const T & value) {
        Assert::fatal((value <= m_max) && (value >= 0), "value must be in range");
        m_value = value;
    }
    
    /// @return percentage of value from minimum value to maximum value
    float percentage() const {
        return (float)m_value / (float)m_max;
    }
    
    /// @param percentage set value to percentage between minimum value (0) and maximum value (1)
    void percentage(const float percentage) {
        Assert::fatal((percentage <= 1) && (percentage >= 0), "percentage (%f) should not be outside bounds [0,0]", percentage);
        m_value = ((m_max - m_min) * percentage) + m_min;
    }
    
private:
    T m_value;
    T m_max;
    T m_min;
};

}
}

#endif /* Slider_hpp */
