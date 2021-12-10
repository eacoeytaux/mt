#ifndef Camera_hpp
#define Camera_hpp

#include "mt.hpp"
#include "geometry.hpp"
#include "Color.hpp"

namespace mt {

class Camera {
public:
    Camera(const Coordinate & center = Coordinate(), float width = 0, float height = 0, float zoom = 1);
    
    void update();
    
#ifdef MT_DEBUG
    void draw_vector(const Color &, const Vector &, const unsigned int thickness, const unsigned int arrow_shaft_length, const unsigned int arrow_head_length) const;
#endif
    void draw_line(const Color &, const Line &, const unsigned int thickness = 1, const float z = 1) const;
    void draw_lines(const Color &, const Path &, const unsigned int thickness = 1, const float z = 1) const; // TODO change to paths
    void draw_lines(const Colors &, const Path &, const unsigned int thickness = 1, const float z = 1) const; // TODO change to paths
    void draw_triangle(const Color &, const Triangle &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_triangle(const Colors &, const Triangle &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_rectangle(const Color &, const Rectangle &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_rectangle(const Colors &, const Rectangle &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_square(const Color &, const Square &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_square(const Colors &, const Square &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_polygon(const Color &, const Polygon &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_polygon(const Colors &, const Polygon &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_circle(const Color &, const Circle &, const unsigned int thickness = FILLED_, const float z = 1) const;
    void draw_circle(const Colors &, const Circle &, const unsigned int thickness = FILLED_, const float z = 1) const;
//    void draw_shape(const Color &, const Shape &, const unsigned int thickness = FILLED_, const float z = 1) const;
//    void draw_shape(const Colors &, const Shape &, const unsigned int thickness = FILLED_, const float z = 1) const;
    
    float width() const;
    void width(float);
    float height() const;
    void height(float);
    Coordinate center() const;
    void center(const Coordinate &);
    Coordinate target() const;
    void target(const Coordinate &);
    float zoom() const;
    void zoom(float);
    
private:
    float m_width, m_height;
    Coordinate m_center;
    Coordinate m_target;
    float m_zoom, m_zoom_target;
    
    const float m_movement_ratio = 0.5;
};

}

#endif /* Camera_hpp */
