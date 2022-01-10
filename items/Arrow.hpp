#ifndef Arrow_hpp
#define Arrow_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class Arrow
/// @brief projectile weapon fired by a bow
class Arrow : public Object {
public:
    virtual ~Arrow() { }
    Arrow(World*, const Coordinate & tip, const Vector & launch_speed, const Color & feather_color = Random::r_Color());
    
    void update(float dt = 1) override;
    void draw(const Camera *) const override;
    
    float width() const override;
    
private:
    Color m_feather_color;

};

}
}

#endif /* Arrow_hpp */
