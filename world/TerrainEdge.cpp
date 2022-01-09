#include "TerrainEdge.hpp"

#include "TerrainVertex.hpp"

NAMESPACES
using mt::exst::TerrainEdge;

TerrainEdge::TerrainEdge(shared_ptr<TerrainVertex> _v1, shared_ptr<TerrainVertex> _v2, float _resistance) :
m_v1(_v1),
m_v2(_v2),
m_resistance(_resistance) {
    Assert::fatal(m_v1 != nullptr);
    Assert::fatal(m_v2 != nullptr);
}

TerrainEdge::TerrainEdge(const TerrainEdge & _edge) {
    m_v1 = _edge.vertex1();
    m_v2 = _edge.vertex2();
}

Line TerrainEdge::line() const {
    return Line(m_v2->position(), m_v1->position());
}

shared_ptr<TerrainVertex> TerrainEdge::vertex1() const {
    return m_v1;
}

shared_ptr<TerrainVertex> TerrainEdge::vertex2() const {
    return m_v2;
}

float TerrainEdge::resistance() const {
    return m_resistance;
}
