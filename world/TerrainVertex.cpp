#include "TerrainVertex.hpp"

#include "TerrainEdge.hpp"

NAMESPACES
using mt::exists::TerrainVertex;

TerrainVertex::TerrainVertex(const Coordinate & _pos) {
    m_pos = _pos;
}

Coordinate TerrainVertex::position() const {
    return m_pos;
}

TerrainEdge * TerrainVertex::edge1() const {
    return m_e1;
}

TerrainEdge * TerrainVertex::edge2() const {
    return m_e2;
}
