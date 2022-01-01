#ifndef Darkness_hpp
#define Darkness_hpp

#include "mt.hpp"
#include "Graphics.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

class Darkness : public Visible {
public:
    struct LightSource {
    public:
        LightSource(const Coordinate & source, const float distance, const float flicker = 0);
        LightSource(const Coordinate & source, const float distance, const Color & tint, const float flicker = 0);
        Coordinate position;
        float distance;
        float flicker;
        Color tint;
        
        bool operator==(const LightSource &) const;
        bool operator!=(const LightSource &) const;
    };
    
public:
    Darkness();
    
    void darkness_intensity(const float);
    void add_light_source(const Coordinate & position, const float distance, const float flicker = 0);
    void clear_light_sources();
    
    void draw(const Camera *) const;
    
private:
    void fill_boundary_full(const Camera *, const Rectangle & boundary) const;
    void fill_boundary_edge(const Camera *, const Rectangle & boundary, const LightSource & source, const QUADRANT & quadrant) const;
    void draw_recursive(const Camera *, const Rectangle & boundary, const varray<LightSource> & possible_sources, const varray<LightSource> & sources = { }) const;
    
    varray<LightSource> m_light_sources;
    Slider<float> m_darkness_slider = Slider<float>(1);
};

}
}

#endif /* Darkness_hpp */
