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
    virtual ~Cloud() { }
    Cloud(World *);
    
    static float max_dx();
    static float max_dy();
    
    void draw(const Camera *) const;
    
private:
    varray<_puff> m_puffs;
};

}
}

#endif /* Cloud_hpp */
