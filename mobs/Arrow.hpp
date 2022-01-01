#ifndef Arrow_hpp
#define Arrow_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace util {

/// @class Arrow
/// @brief projectile weapon fired by a bow
class Arrow : public Object {
public:
    virtual ~Arrow() { }
    Arrow(World*, const Coordinate & tip, const Vector & launch_speed);
    
    void update() override;
    void draw(const Camera *) const override;
    
private:
    
};

}
}

#endif /* Arrow_hpp */
