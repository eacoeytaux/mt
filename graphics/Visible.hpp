#ifndef Visible_hpp
#define Visible_hpp

#include "Camera.hpp"

namespace mt {

class Camera;

class Visible {
public:
    virtual void draw(const Camera &) const = 0;
};

}

#endif /* Visible_hpp */
