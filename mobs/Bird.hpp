#ifndef Bird_hpp
#define Bird_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class Feather
/// @brief loose feather
class Feather : public Object {
public:
    virtual ~Feather() { }
    Feather(World *, const Coordinate & position);
    
    void draw(const Camera *) const override;
    
private:
    Color m_color;
};

/// @class Bird
/// @brief a winged flying creatures
class Bird : public Object {
public:
    virtual ~Bird() { }
    Bird(World *, const Coordinate & position);
    
private:
    
};

}
}

#endif /* Bird_hpp */
