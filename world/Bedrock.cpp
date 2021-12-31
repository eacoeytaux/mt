#include "Bedrock.hpp"

NAMESPACES
using mt::exists::Bedrock;

const Color BEDROCK_COLOR(32, 32, 32);

Bedrock::Bedrock() : Terrain() { }

void Bedrock::draw(const Camera * _camera) const {
    if (!Terrain::edges().size()) return;
    
    float bottom_y = _camera->screen().center().y() - _camera->screen().height();
    
    varray<Coordinate> coordinates;
    shared_ptr<TerrainEdge> first_edge = edges()[0];
    coordinates.push_back(Coordinate(first_edge->vertex1()->position().x(), bottom_y));
    coordinates.push_back(first_edge->vertex1()->position());
    shared_ptr<TerrainEdge> last_edge;
    for_each (terrain_edge, edges()) {
        coordinates.push_back(terrain_edge->vertex2()->position());
        last_edge = terrain_edge;
    }
    coordinates.push_back(Coordinate(last_edge->vertex2()->position().x(), bottom_y));
    
    _camera->draw_polygon(BEDROCK_COLOR, Polygon(coordinates));
    
    Terrain::draw(_camera);
}

varray<Line> Bedrock::camera_buffer(const Camera * _camera) const {
    varray<Line> buffer;
//    if (edges().size()) buffer.push_back(Line(edges()[0]->vertex1()->position(), edges()[edges().size()-1]->vertex2()->position()) + Vector(0, (_camera->height() / 2) * 1/2));
    for_each (edge, edges()) buffer.push_back(edge->line() + Vector(0, (_camera->height() / 2) * 2/3));
    return buffer;
}
