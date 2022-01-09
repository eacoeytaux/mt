#ifndef __Coordinate__
#define __Coordinate__

#include "mt.hpp"

namespace mt {

namespace geometry {

class Angle;
class Vector;

/// @brief cartesian coordinate quadrants
enum QUADRANT {
    NO_QUADRANT = -1, // origin or axes
    Q1 = 0,
    Q2 = 1,
    Q3 = 2,
    Q4 = 3,
    QUADRANTS
};

/// @brief cartesian coordinate axes
enum AXIS {
    NO_AXIS = -1, // origin or quadrant
    X_AXIS = 0,
    Y_AXIS = 1,
    AXES
};

//#define Coordinates std::vector<Coordinate>

/// @class Coordinate
/// @brief cartesian coordinate
class Coordinate {
public:
    /// @param x x
    /// @param y y
    Coordinate(float x = 0, float y = 0);
    
    /// @return x
    float x() const;
    /// @param x x
    Coordinate & x(float x);
    
    /// @return y
    float y() const;
    /// @param y y
    Coordinate & y(float y);
    
    /// @param coordinate coordinate to measure distance from
    /// @return distance from coordinate
    float distance(const Coordinate & coordinate) const;
    
    /// @param angle angle to rotate by
    /// @param origin origin to rotate around, default true origin
    Coordinate & rotate_about(const Angle & angle, const Coordinate & origin = Coordinate(0, 0));
    
    /// @return which quadrant coordinate is in if any
    QUADRANT quadrant() const;
    /// @return which axis coordinate is on if any
    AXIS axis() const;
    
    /// @param quadrant quadrant to check
    /// @return whether or not coordinate is in quadrant
    bool in_quadrant(QUADRANT quadrant) const;
    /// @param axis axis to check
    /// @return whether or not coordinate is on axis
    bool on_axis(AXIS axis) const;
    
    Coordinate operator+(const Vector & vector) const;
    Coordinate & operator+=(const Vector & vector);
    Coordinate operator-(const Vector & vector) const;
    Coordinate & operator-=(const Vector & vector);
    
    bool operator==(const Coordinate & coordinate) const;
    bool operator!=(const Coordinate & coordinate) const;
    
private:
    float m_x;
    float m_y;
};

const Coordinate COORDINATE_POS_INFINITY(POS_INFINITY, POS_INFINITY);
const Coordinate COORDINATE_NEG_INFINITY(NEG_INFINITY, NEG_INFINITY);

}
}

#endif /* defined(__Coordinate__) */
