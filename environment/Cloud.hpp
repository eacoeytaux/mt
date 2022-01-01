#ifndef Cloud_hpp
#define Cloud_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

class Cloud : public Object {
private:
    struct _puff {
    public:
        _puff(float radius, const Vector & center_offset);
        float m_radius;
        Vector m_center_offset;
    };
    
public:
    Cloud(World*);
    
    float max_dx() const;
    float max_dy() const;
    
    void update();
    void draw(const Camera *) const;
    
private:
    varray<_puff> m_puffs;
};

}
}

#endif /* Cloud_hpp */
