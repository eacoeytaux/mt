#ifndef Sky_hpp
#define Sky_hpp

#include "mt.hpp"
#include "Object.hpp"
#include "Cloud.hpp"

namespace mt {
namespace exst {

/// @class Sky
/// @brief most background visual layer
class Sky : public Object {
public:
    Sky(World*, int cloud_regen_rate = 0);
    
    void update(float dt = 1);
    void draw(const Camera *) const;
    
private:
    varray<shared_ptr<Cloud>> m_clouds;
    int m_cloud_regen_rate; // 0 means never, 1 means most clouds, high number means few
    Timer m_cloud_timer;
    Color m_top_color;
    Color m_bottom_color;
};

}
}

#endif /* Sky_hpp */
