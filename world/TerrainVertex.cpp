#include "TerrainVertex.hpp"

#include "TerrainEdge.hpp"

NAMESPACES
using mt::exst::TerrainVertex;

TerrainVertex::TerrainVertex(const Coordinate & _pos) {
    m_pos = _pos;
}

Coordinate TerrainVertex::position() const {
    return m_pos;
}

shared_ptr<TerrainEdge> TerrainVertex::edge1() const {
    return m_e1;
}

shared_ptr<TerrainEdge> TerrainVertex::edge2() const {
    return m_e2;
}
