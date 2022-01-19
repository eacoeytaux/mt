#ifndef Sprite_hpp
#define Sprite_hpp

#include "mt.hpp"
#include "Color.hpp"
#include "geometry.hpp"

namespace mt {
namespace graphics {

/// @class Sprite
/// @brief template file
class Sprite {
public:
    struct ColoredPolygon {
        Polygon shape;
        varray<Color> colors;
        uint thickness;
    };
    
public:
    virtual ~Sprite() { }
    Sprite(const varray<ColoredPolygon> & shapes = {});
    
    varray<ColoredPolygon> shapes() const;

    Sprite & clear();
    Sprite & add_sprite(const Sprite &);
    Sprite & add_shape(const ColoredPolygon &);
    Sprite & add_shape(const Line & line, const Color & color, uint thickness = FILLED);
    Sprite & add_shape(const Shape & shape, const Color & color, uint thickness = FILLED);
    Sprite & add_shape(const Shape & shape, const varray<Color> & colors, uint thickness = FILLED);
    
private:
    varray<ColoredPolygon> m_shapes;
};

}
}

#endif /* Sprite_hpp */
