#ifndef __Coordinate__
#define __Coordinate__

#include "mt.hpp"

namespace mt {

class Angle;
class Vector;

enum QUADRANT {
    NO_QUADRANT = -1, // origin or axes
    Q1 = 0,
    Q2 = 1,
    Q3 = 2,
    Q4 = 3,
    QUADRANTS
};

enum AXIS {
    NO_AXIS = -1, // origin or quadrant
    X_AXIS = 0,
    Y_AXIS = 1,
    AXES
};

//#define Coordinates std::vector<Coordinate>

class Coordinate {
public:
    Coordinate(float x = 0, float y = 0);
    
    float x() const;
    void x(float x);
    
    float y() const;
    void y(float y);
    
    float distance(const Coordinate &) const;
    
    QUADRANT quadrant() const;
    AXIS axis() const;
    
    bool in_quadrant(QUADRANT) const;
    bool on_axis(AXIS) const;
    
    Coordinate operator+(const Vector &) const;
    Coordinate & operator+=(const Vector &);
    Coordinate operator-(const Vector &) const;
    Coordinate & operator-=(const Vector &);
    
    bool operator==(const Coordinate &) const;
    bool operator!=(const Coordinate &) const;
    
private:
    float m_x;
    float m_y;
};

const Coordinate COORDINATE_POS_INFINITY(POS_INFINITY, POS_INFINITY);
const Coordinate COORDINATE_NEG_INFINITY(NEG_INFINITY, NEG_INFINITY);

}

#endif /* defined(__Coordinate__) */
