#ifndef Square_hpp
#define Square_hpp

#include "Rectangle.hpp"

//#define Squares varray<Square>

namespace mt {

class Square : public Rectangle {
public:
    Square(float width = 0, const Coordinate & center = Coordinate(), const Angle & angle = Angle());
    
    void width(const float);
    void height(const float);
};

}

#endif /* Square_hpp */
