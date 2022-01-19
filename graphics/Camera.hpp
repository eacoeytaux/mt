#ifndef Camera_hpp
#define Camera_hpp

#include "mt.hpp"
#include "Color.hpp"
#include "Sprite.hpp"
#include "Geometry.hpp"

namespace mt {
namespace graphics {

/// @class Camera
/// @brief projects objects to screen
class Camera {
public:
    virtual ~Camera() { }
    Camera(const Coordinate & center = Coordinate(), float width = 0, float height = 0, float zoom = 1);
    
    void render() const;
#ifdef MT_DEBUG
    void debug_overlay() const;
#endif
    void update(float dt = 1);
    
    Rectangle screen() const;
    
    void draw_sprite(const Sprite & sprite, const Coordinate & position, const float z = 1) const;
#ifdef MT_DEBUG
    void draw_vector(const Color &, const Vector &, const unsigned int thickness, const unsigned int arrow_shaft_length, const unsigned int arrow_head_length) const;
#endif
    
    void draw_line(const Color &, const Line &, const unsigned int thickness = 1, const float z = 1) const;
    void draw_lines(const Colors &, const varray<Line> &, const unsigned int thickness = 1, const float z = 1) const;
    void draw_shape(const Color &, const Shape &, const unsigned int thickness = FILLED, const float z = 1) const;
    void draw_shape(const Colors &, const Shape &, const unsigned int thickness = FILLED, const float z = 1) const;
    
//    void draw_triangle(const Color &, const Triangle &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_triangle(const Colors &, const Triangle &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_rectangle(const Color &, const Rectangle &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_rectangle(const Colors &, const Rectangle &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_square(const Color &, const Square &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_square(const Colors &, const Square &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_polygon(const Color &, const Polygon &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_polygon(const Colors &, const Polygon &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_circle(const Color &, const Circle &, const unsigned int thickness = FILLED, const float z = 1) const;
//    void draw_circle(const Colors &, const Circle &, const unsigned int thickness = FILLED, const float z = 1) const;
    
    float width() const;
    void width(const float);
    float height() const;
    void height(const float);
    Coordinate center() const;
    void center(const Coordinate &);
    Coordinate target() const;
    void target(const Coordinate &);
    float zoom() const;
    void zoom(const float);
    
private:
    Vector center_offset() const;
    
    float m_width, m_height;
    Coordinate m_center;
    Coordinate m_target;
    float m_zoom = 1;
    
    const float m_movement_ratio = 0.5;
};

}
}

#endif /* Camera_hpp */
