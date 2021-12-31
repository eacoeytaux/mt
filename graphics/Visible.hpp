#ifndef Visible_hpp
#define Visible_hpp

#include "Camera.hpp"

namespace mt {
namespace graphics {

class Camera;

/// @class Visible
/// @brief anything that is visible
class Visible {
public:
    virtual void draw(const Camera *) const = 0;
};

}
}

#endif /* Visible_hpp */
