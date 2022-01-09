#include "Terrain.hpp"

#include "Random.hpp"

NAMESPACES
using mt::exst::Terrain;

const int THICKNESS = 6;
const int OUTLINE_THICKNESS = 3;
const Color GRASS_COLOR_LIGHT = Color(0, 192, 0);
const Color GRASS_COLOR_DARK = Color(0, 127, 0);

Terrain::Terrain(World * world) : Object(world, Coordinate(), 0, 0, 1) {
    layer_position(1);
    m_gravity_ratio = 0;
    
    shared_ptr<TerrainVertex> v0(new TerrainVertex(Coordinate(-800, 0)));
    shared_ptr<TerrainVertex> v1(new TerrainVertex(Coordinate(-100, 5)));
    shared_ptr<TerrainVertex> v2(new TerrainVertex(Coordinate(100, 25)));
    shared_ptr<TerrainVertex> v3(new TerrainVertex(Coordinate(200, 100)));
    shared_ptr<TerrainVertex> v4(new TerrainVertex(Coordinate(350, 75)));
    shared_ptr<TerrainVertex> v5(new TerrainVertex(Coordinate(500, 25)));
    shared_ptr<TerrainVertex> v6(new TerrainVertex(Coordinate(800, 0)));
    
    shared_ptr<TerrainEdge> e0(new TerrainEdge(v0, v1));
    v0->m_e2 = e0;
    v1->m_e1 = e0;
    shared_ptr<TerrainEdge> e1(new TerrainEdge(v1, v2));
    v1->m_e2 = e1;
    v2->m_e1 = e1;
    shared_ptr<TerrainEdge> e2(new TerrainEdge(v2, v3));
    v2->m_e2 = e2;
    v3->m_e1 = e2;
    shared_ptr<TerrainEdge> e3(new TerrainEdge(v3, v4));
    v3->m_e2 = e3;
    v4->m_e1 = e3;
    shared_ptr<TerrainEdge> e4(new TerrainEdge(v4, v5));
    v4->m_e2 = e4;
    v5->m_e1 = e4;
    shared_ptr<TerrainEdge> e5(new TerrainEdge(v5, v6));
    v5->m_e2 = e5;
    v6->m_e1 = e5;
    
    m_vertices.push_back(v0);
    m_vertices.push_back(v1);
    m_vertices.push_back(v2);
    m_vertices.push_back(v3);
    m_vertices.push_back(v4);
    m_vertices.push_back(v5);
    m_vertices.push_back(v6);
    
    m_edges.push_back(e0);
    m_edges.push_back(e1);
    m_edges.push_back(e2);
    m_edges.push_back(e3);
    m_edges.push_back(e4);
    m_edges.push_back(e5);
}

void Terrain::update(float dt) {
    Object::update(dt);
}

void Terrain::draw(const Camera * _camera) const {
    for_each (vertex, vertices()) {
        _camera->draw_polygon(GRASS_COLOR_DARK, Polygon(8, (THICKNESS / 2) + OUTLINE_THICKNESS, vertex->position()));
    }
    for_each (edge, edges()) {
        _camera->draw_line(GRASS_COLOR_DARK, edge->line(), THICKNESS + (OUTLINE_THICKNESS * 2));
    }
    for_each (vertex, vertices()) {
        _camera->draw_polygon(GRASS_COLOR_LIGHT, Polygon(8, THICKNESS / 2, vertex->position()));
    }
    for_each (edge, edges()) {
        if (edge->vertex1() && edge->vertex2())
            _camera->draw_line(GRASS_COLOR_LIGHT, edge->line(), THICKNESS);
    }
    
//    for_each (edge : m_edges) {
//        Random::seed(edge->vertex1()->position().x() * edge->vertex1()->position().y());
//
//        Line edge_line(edge->vertex1()->position(), edge->vertex2()->position());
//        float x_min = edge_line.left().x();
//        float x_max = edge_line.right().x();
//
////        for (float x = x_min; x < x_max; x += thickness) {
////            int skip = Random::r_int(4, 8);
////            while (skip-- > 0) {
////                x += thickness;
////            }
////            float stem_width = thickness * Random::r_int(1, 4);
////            camera.draw_polygon(GRASS_COLOR_DARK, Polygon::Equilateral(Random::r_int(5, 8), Coordinate(x, edge_line.y(x) - Random::r_int(8, 20)), stem_width, Random::r_Angle()));
////        }
//
//        for (float x = x_min; x < x_max; x += THICKNESS) {
//            float stem_width = THICKNESS * 5;
//            _camera->draw_rectangle(GRASS_COLOR_DARK, Rectangle(stem_width, stem_width, Coordinate(x, edge_line.y(x)), Random::r_Angle()));
//        }
//    }
//
//    for_each (edge : m_edges) {
//        Line edge_line(edge->vertex1()->position(), edge->vertex2()->position());
//        float x_min = edge_line.left().x();
//        float x_max = edge_line.right().x();
//
//        for (float x = x_min; x < x_max; x += THICKNESS) {
//            float stem_width = THICKNESS * 2;
//            _camera->draw_rectangle(GRASS_COLOR_LIGHT, Rectangle(stem_width, stem_width, Coordinate(x, edge_line.y(x)), Random::r_Angle()));
//        }
//    }
}

const varray<shared_ptr<TerrainVertex>> & Terrain::vertices() const {
    return m_vertices;
}

const varray<shared_ptr<TerrainEdge>> & Terrain::edges() const {
    return m_edges;
}
