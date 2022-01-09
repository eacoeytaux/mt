#ifndef IcePick_hpp
#define IcePick_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class IcePick
/// @brief template file
class IcePick : public Object {
public:
    virtual ~IcePick() { }
    IcePick(World *, const Coordinate & position);
    
    void update();
    void draw(const Camera *) const;
    
private:
    
};

}
}

#endif /* IcePick_hpp */
