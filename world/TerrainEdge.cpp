#include "TerrainEdge.hpp"

#include "TerrainVertex.hpp"

NAMESPACES
using mt::exists::TerrainEdge;

TerrainEdge::TerrainEdge(shared_ptr<TerrainVertex> _v1, shared_ptr<TerrainVertex> _v2) :
m_v1(_v1.get()),
m_v2(_v2.get()) {
    m_v1->m_e2 = this;
    m_v2->m_e1 = this;
}

TerrainEdge::TerrainEdge(const TerrainEdge & _edge) {
    m_v1 = _edge.vertex1();
    m_v2 = _edge.vertex2();
}

Line TerrainEdge::line() const {
    return Line(m_v2->position(), m_v1->position());
}

TerrainVertex * TerrainEdge::vertex1() const {
    return m_v1;
}

TerrainVertex * TerrainEdge::vertex2() const {
    return m_v2;
}
