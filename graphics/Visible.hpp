#ifndef Visible_hpp
#define Visible_hpp

#include "Camera.hpp"

namespace mt {
namespace graphics {

class Camera;

const uint LAYER_BACK = 0;
const uint LAYER_PLAYER = 128;

/// @class Visible
/// @brief anything that is visible
class Visible {
public:
    virtual ~Visible() { }
    
    virtual void draw(const Camera *) const = 0;
    
    Visible(uint layer_position = 0) : m_layer_position(layer_position) { }
    uint layer_position() const { return m_layer_position; }
    Visible & layer_position(uint layer_position) { m_layer_position = layer_position; return *this; }
private:
    uint m_layer_position;
};

}
}

#endif /* Visible_hpp */
