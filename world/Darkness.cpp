#include "Darkness.hpp"

using namespace mt;

Darkness::LightSource::LightSource(const Coordinate & _position, const float _distance, const float _flicker) {
    position = _position;
    distance = _distance;
    flicker = _flicker;
    tint = Color(GREEN, 64);
}

Darkness::LightSource::LightSource(const Coordinate & _position, const float _distance, const Color & _tint, const float _flicker) {
    position = _position;
    distance = _distance;
    flicker = _flicker;
    tint = _tint;
    tint = Color(GREEN, 64); // TODO delete
}

bool Darkness::LightSource::operator==(const LightSource & _light_source) const {
    return ((position == _light_source.position) && (distance == _light_source.distance) && (flicker == _light_source.flicker));
}

bool Darkness::LightSource::operator!=(const LightSource & _light_source) const {
    return !(*this == _light_source);
}

Darkness::Darkness() {
    m_darkness_slider.value(0);
}

void Darkness::darkness_intensity(const float _intensity) {
    m_darkness_slider.value(_intensity);
}

void Darkness::add_light_source(const Coordinate & _position, const float _distance, const float _flicker) {
    m_light_sources.push_back(LightSource(_position, _distance, _flicker));
}

void Darkness::clear_light_sources() {
    m_light_sources.clear();
}

void Darkness::draw(const Camera & _camera) const {
    if (!m_darkness_slider.value()) return;
    
    Random::seed(0); // TODO
    Rectangle full(_camera.width(), _camera.height(), _camera.center());
    draw_recursive(_camera, full, m_light_sources, { });
    
    for_each (light, m_light_sources) {
        _camera.draw_circle(Color(WHITE, 64), Circle(light.distance, light.position));
    }
}

void Darkness::fill_boundary_full(const Camera & _camera, const Rectangle & _boundary) const {
    Rectangle boundary = _boundary;
//    boundary.center(Coordinate(ceil(_boundary.center().x()), ceil(_boundary.center().y())));
//    boundary.width(ceil(boundary.width()));
//    boundary.height(ceil(boundary.height()));
    _camera.draw_rectangle(Color(BLACK, m_darkness_slider.value() * 255 / 2), boundary);
}

void Darkness::fill_boundary_edge(const Camera & _camera, const Rectangle & _boundary, const LightSource & _source, const QUADRANT & _quadrant) const {
    Vector v1;
    Vector v2;
    if ((_quadrant == Q1) || (_quadrant == Q3)) {
        v1 = Vector(_source.position, _boundary.top_left());
        v2 = Vector(_source.position, _boundary.bottom_right());
    } else if ((_quadrant == Q2) || (_quadrant == Q4)) {
        v1 = Vector(_source.position, _boundary.top_right());
        v2 = Vector(_source.position, _boundary.bottom_left());
    }
    
    Path arc = Circle(_source.distance, _source.position).arc(v1.angle(), v2.angle());
//    _camera.draw_lines(CYAN, arc);
    
    _camera.draw_line(Color(WHITE, 127), Line(v1.destination(), v2.destination()));
    _camera.draw_rectangle(_source.tint, _boundary);
//    _camera.draw_rectangle(RED, _boundary, 2);
}

void Darkness::draw_recursive(const Camera & _camera, const Rectangle & _rectangle, const varray<LightSource> & _possible_sources, const varray<LightSource> & _sources) const {
    if (!_rectangle.area()) return;
    
    varray<LightSource> new_sources;
    for_each (source, _sources) {
        Coordinate farthest, closest;
        Angle d_angle(Vector(source.position, _rectangle.center()).angle().radians(), true);
        QUADRANT quadrant = d_angle.quadrant();
        switch (quadrant) {
            case Q1:
                farthest = _rectangle.top_right();
                closest = _rectangle.bottom_left();
                break;
            case Q2:
                farthest = _rectangle.top_left();
                closest = _rectangle.bottom_right();
                break;
            case Q3:
                farthest = _rectangle.bottom_left();
                closest = _rectangle.top_right();
                break;
            case Q4:
                farthest = _rectangle.bottom_right();
                closest = _rectangle.top_left();
                break;
            default:
                continue;
        }
        
        // section is entirely emersed in light, no need to recurse further
        if (source.position.distance(farthest) + 1 < source.distance) {
            _camera.draw_rectangle(source.tint, _rectangle);
            return;
        }
        
        if (source.position.distance(closest) + 1 < source.distance) {
            new_sources.push_back(source);
        }
    }
    
    for_each (light, _possible_sources) {
        Rectangle boundary = _rectangle;
        // expand to include radius instead of just center
        boundary.width(boundary.width() + (light.distance * 2));
        boundary.height(boundary.height() + (light.distance * 2));
        if (boundary.contains(light.position)) {
            
            // found new light source, recurse further
            
            new_sources.push_back(light);
            
            Circle light_circle(light.distance, light.position);
            Rectangle light_boundary(light.distance * 2, light.distance * 2, light.position);
            Rectangle::RectangleSplit split_rectangles = _rectangle.split(light.position);
            
            // TODO this could probably be narrowed down than creating a max of 16 recursive branches, maybe 5?
            // if it was created as such:
            //
            // 4|2|5
            // 4|2|5
            // 4|-|5
            // 4|1|5
            // 4|-|5
            // 4|3|5
            // 4|3|5
            //
            // where 1 has the source
            // then light sources could be sorted by x and narrowed down much more

            for_range (4) {
                Rectangle rectangle = split_rectangles[i];
                if (rectangle.area()) {
                    varray<LightSource> split_sources;
                    for_each (possible_light, _possible_sources) {
                        if (possible_light == light) continue;
                        Rectangle boundary = rectangle;
                        boundary.width(boundary.width() + (possible_light.distance * 2) - 1);
                        boundary.height(boundary.height() + (possible_light.distance * 2)  - 1);
                        if (boundary.contains(possible_light.position)) {
                            split_sources.push_back(possible_light);
                        }
                    }
                    Rectangle::RectangleSplit rectangle_split = rectangle.split(light_boundary.lines()[i].c1());
                    for_each (rectangle_split_split, rectangle_split) {
                        draw_recursive(_camera, rectangle_split_split, split_sources, new_sources);
                    }
                }
            }
            
            return;
        }
    }
    
    if (!new_sources.size()) {
        fill_boundary_full(_camera, _rectangle);
        return;
    }
    
    else if (new_sources.size() == 1) {
        LightSource source = new_sources[0];
        Circle subtraction(source.distance, source.position);
        
        Angle d_angle(Vector(subtraction.center(), _rectangle.center()).angle().radians(), true);
        QUADRANT quadrant = d_angle.quadrant();
        
        Coordinate c1;
        Coordinate c2;
        
        switch (quadrant) {
            case Q1:
                c1 = _rectangle.bottom_right();
                c2 = _rectangle.top_left();
                break;
            case Q2:
                c1 = _rectangle.bottom_left();
                c2 = _rectangle.top_right();
                break;
            case Q3:
                c1 = _rectangle.top_left();
                c2 = _rectangle.bottom_right();
                break;
            case Q4:
                c1 = _rectangle.top_right();
                c2 = _rectangle.bottom_left();
                break;
            default:
                break;
        }
        
        float x_ratio = subtraction.center().distance(c1) / subtraction.radius();
        float y_ratio = subtraction.center().distance(c2) / subtraction.radius();
        
        bool x_ratio_greater = float_ge(x_ratio, 1);
        bool y_ratio_greater = float_ge(y_ratio, 1);
            
        Coordinate split_point;
        
        if ((quadrant == Q1)) {
        
        if (x_ratio_greater && y_ratio_greater) { // TODO
                
            if (quadrant == Q1) {
                split_point = Coordinate(subtraction.x_high(_rectangle.lower_bound_y()), subtraction.y_high(_rectangle.lower_bound_x()));
            } else if (quadrant == Q2) {
                split_point = Coordinate(subtraction.x_low(_rectangle.lower_bound_y()), subtraction.y_high(_rectangle.upper_bound_x()));
            } else if (quadrant == Q3) {
                split_point = Coordinate(subtraction.x_low(_rectangle.upper_bound_y()), subtraction.center().y() - (subtraction.y_high(_rectangle.upper_bound_x()) - subtraction.center().y()));
            } else if (quadrant == Q4) {
                split_point = Coordinate(subtraction.x_low(_rectangle.upper_bound_y()), subtraction.center().y() - (subtraction.y_high(_rectangle.upper_bound_x()) - subtraction.center().y()));
            } else {
                Assert::soft(false);
            }
            
            Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
            
            for_range (q, QUADRANTS) {
                if (quadrant == Q2) { // idk why this one is special
                    if (q != Q2) fill_boundary_full(_camera, rectangle_split[q]);
                    else fill_boundary_edge(_camera, rectangle_split[q], source, quadrant);
                    continue;
                }
                
                if (q != ((quadrant + 2) % 4)) fill_boundary_full(_camera, rectangle_split[q]);
                else fill_boundary_edge(_camera, rectangle_split[q], source, quadrant);
            }
        } else if (x_ratio_greater || y_ratio_greater) {
            switch (quadrant) {
                case Q1:
                    split_point = x_ratio_greater ? Coordinate(subtraction.x_high(_rectangle.upper_bound_y()), _rectangle.upper_bound_y()) : Coordinate(_rectangle.upper_bound_x(), subtraction.y_high(_rectangle.upper_bound_x()));
                    break;
                case Q2:
                    split_point = x_ratio_greater ? Coordinate(subtraction.x_low(_rectangle.upper_bound_y()), _rectangle.upper_bound_y()) : Coordinate(_rectangle.lower_bound_x(), subtraction.y_high(_rectangle.lower_bound_x()));
                    break;
                case Q3:
                    split_point = x_ratio_greater ? Coordinate(subtraction.x_low(_rectangle.lower_bound_y()), _rectangle.lower_bound_y()) : Coordinate(_rectangle.lower_bound_x(), subtraction.y_low(_rectangle.lower_bound_x()));
                    break;
                case Q4:
                    split_point = x_ratio_greater ? Coordinate(subtraction.x_high(_rectangle.lower_bound_y()), _rectangle.lower_bound_y()) : Coordinate(_rectangle.upper_bound_x(), subtraction.y_low(_rectangle.upper_bound_x()));
                    break;
                default:
                    Assert::soft(false);
                    return;
            }
            
            Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
            
            Rectangle edge_boundary;
            int edge_boundary_split_index = 0;
            switch (quadrant) {
                case Q1:
                    edge_boundary_split_index = x_ratio_greater ? 3 : 1;
                    edge_boundary = x_ratio_greater ? rectangle_split.bottom_right() : rectangle_split.top_left();
                    break;
                case Q2:
                    edge_boundary_split_index = x_ratio_greater ? 2 : 0;
                    edge_boundary = x_ratio_greater ? rectangle_split.bottom_left() : rectangle_split.top_right();
                    break;
                case Q3:
                    edge_boundary_split_index = x_ratio_greater ? 1 : 3;
                    edge_boundary = x_ratio_greater ? rectangle_split.top_left() : rectangle_split.bottom_right();
                    break;
                case Q4:
                    edge_boundary_split_index = x_ratio_greater ? 0 : 2;
                    edge_boundary = x_ratio_greater ? rectangle_split.top_right() : rectangle_split.bottom_left();
                    break;
                default:
                    Assert::soft(false);
                    return;
            }
            fill_boundary_edge(_camera, rectangle_split[edge_boundary_split_index], source, quadrant);
//            fill_boundary_edge(_camera, edge_boundary, subtraction, quadrant);
            
            for_range (q, QUADRANTS) {
                if (edge_boundary_split_index != q) _camera.draw_rectangle(source.tint, rectangle_split[q]);
            }
        } else {
            _camera.draw_rectangle(Color(YELLOW, 64), _rectangle);
        }
            
        }
        
        if (d_angle < PI * 1/2) {
//            float x_ratio = subtraction.center().distance(_rectangle.bottom_right()) / subtraction.radius();
//            float y_ratio = subtraction.center().distance(_rectangle.top_left()) / subtraction.radius();
//
//            if (x_ratio_greater && y_ratio_greater) { // TODO
//                Coordinate split_point = Coordinate(subtraction.x_high(_rectangle.lower_bound_y()), subtraction.y_high(_rectangle.lower_bound_x()));
//                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
//                fill_boundary_full(_camera, rectangle_split.top_right());
//                fill_boundary_full(_camera, rectangle_split.bottom_right());
//                fill_boundary_full(_camera, rectangle_split.top_left());
//                fill_boundary_edge(_camera, rectangle_split.bottom_left(), subtraction, Q1);
//            } else if x_ratio_greater {
//                Coordinate split_point = Coordinate(subtraction.x_high(_rectangle.upper_bound_y()), _rectangle.upper_bound_y());
//                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
//                fill_boundary_edge(_camera, rectangle_split.bottom_right(), subtraction, Q1);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
//            } else if y_ratio_greater {
//                Coordinate split_point = Coordinate(_rectangle.upper_bound_x(), subtraction.y_high(_rectangle.upper_bound_x()));
//                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
//                fill_boundary_edge(_camera, rectangle_split.top_left(), subtraction, Q1);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
//            } else {
//                _camera.draw_rectangle(Color(YELLOW, 64), _rectangle);
//            }
        } else if (d_angle < PI) {
            float x_ratio = subtraction.center().distance(_rectangle.bottom_left()) / subtraction.radius();
            float y_ratio = subtraction.center().distance(_rectangle.top_right()) / subtraction.radius();

            if (x_ratio_greater && y_ratio_greater) { // TODO
                Coordinate split_point = Coordinate(subtraction.x_low(_rectangle.lower_bound_y()), subtraction.y_high(_rectangle.upper_bound_x()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_full(_camera, rectangle_split.top_right());
                fill_boundary_full(_camera, rectangle_split.bottom_left());
                fill_boundary_full(_camera, rectangle_split.top_left());
                fill_boundary_edge(_camera, rectangle_split.bottom_right(), source, Q2);
            } else if (x_ratio_greater) {
                Coordinate split_point = Coordinate(subtraction.x_low(_rectangle.upper_bound_y()), _rectangle.upper_bound_y());
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.bottom_left(), source, Q2);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
            } else if (y_ratio_greater) {
                Coordinate split_point = Coordinate(_rectangle.lower_bound_x(), subtraction.y_high(_rectangle.lower_bound_x()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.top_right(), source, Q2);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
            } else {
                _camera.draw_rectangle(Color(MAGENTA, 64), _rectangle);
            }
        } else if (d_angle < PI * 1.5) {
            float x_ratio = subtraction.center().distance(_rectangle.top_left()) / subtraction.radius();
            float y_ratio = subtraction.center().distance(_rectangle.bottom_right()) / subtraction.radius();

            if (x_ratio_greater && y_ratio_greater) { // TODO
                Coordinate split_point = Coordinate(subtraction.x_low(_rectangle.upper_bound_y()), subtraction.center().y() - (subtraction.y_high(_rectangle.upper_bound_x()) - subtraction.center().y()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_full(_camera, rectangle_split.bottom_right());
                fill_boundary_full(_camera, rectangle_split.bottom_left());
                fill_boundary_full(_camera, rectangle_split.top_left());
                fill_boundary_edge(_camera, rectangle_split.top_right(), source, Q3);
            } else if (x_ratio_greater) {
                Coordinate split_point = Coordinate(subtraction.x_low(_rectangle.lower_bound_y()), _rectangle.lower_bound_y());
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.top_left(), source, Q3);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
            } else if (y_ratio_greater) {
                Coordinate split_point = Coordinate(_rectangle.lower_bound_x(), subtraction.y_low(_rectangle.lower_bound_x()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.bottom_right(), source, Q3);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
            } else {
                _camera.draw_rectangle(Color(MAGENTA, 64), _rectangle);
            }
        } else { // if (d_angle < PI * 2) {
            float x_ratio = subtraction.center().distance(_rectangle.top_right()) / subtraction.radius();
            float y_ratio = subtraction.center().distance(_rectangle.bottom_left()) / subtraction.radius();

            if (x_ratio_greater && y_ratio_greater) { // TODO
                Coordinate split_point = Coordinate(subtraction.x_high(_rectangle.upper_bound_y()), subtraction.y_low(_rectangle.lower_bound_x()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_full(_camera, rectangle_split.top_right());
                fill_boundary_full(_camera, rectangle_split.bottom_right());
                fill_boundary_full(_camera, rectangle_split.bottom_left());
                fill_boundary_edge(_camera, rectangle_split.top_left(), source, Q4);
            } else if (x_ratio_greater) {
                Coordinate split_point = Coordinate(subtraction.x_high(_rectangle.lower_bound_y()), _rectangle.lower_bound_y());
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.top_right(), source, Q4);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_left());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
            } else if (y_ratio_greater) {
                Coordinate split_point = Coordinate(_rectangle.upper_bound_x(), subtraction.y_low(_rectangle.upper_bound_x()));
                Rectangle::RectangleSplit rectangle_split = _rectangle.split(split_point);
                fill_boundary_edge(_camera, rectangle_split.bottom_left(), source, Q4);
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.bottom_right());
//                _camera.draw_rectangle(Color(GREEN, 64), rectangle_split.top_left());
            } else {
                _camera.draw_rectangle(Color(MAGENTA, 64), _rectangle);
            }
        }
    }
    
    else if (new_sources.size() > 1) {
        _camera.draw_rectangle(Color(RED, 64), _rectangle);
    }
}
