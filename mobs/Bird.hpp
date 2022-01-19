#ifndef Bird_hpp
#define Bird_hpp

#include "mt.hpp"
#include "Mob.hpp"

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
class Bird : public Mob {
public:
    virtual ~Bird() { }
    Bird(World *, const Coordinate & position);
    
    virtual void kill() override;
    
    virtual void update(float dt) override;
    virtual void draw(const Camera *) const override;
    
private:
    
};

}
}

#endif /* Bird_hpp */
