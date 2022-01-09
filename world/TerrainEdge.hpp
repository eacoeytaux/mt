#ifndef TerrainEdge_hpp
#define TerrainEdge_hpp

#include "mt.hpp"
#include "Geometry.hpp"

namespace mt {
namespace exst {

class TerrainVertex;
class TerrainEdge {
public:
    friend class Terrain;
    TerrainEdge(shared_ptr<TerrainVertex> v1, shared_ptr<TerrainVertex> v2, float resistance = 0.99);
    TerrainEdge(const TerrainEdge &);
    
    Line line() const;
    shared_ptr<TerrainVertex> vertex1() const;
    shared_ptr<TerrainVertex> vertex2() const;
    
    float resistance() const;
    
private:
    shared_ptr<TerrainVertex> m_v1 = nullptr;
    shared_ptr<TerrainVertex> m_v2 = nullptr;
    
    float m_resistance;
};

}
}

#endif /* TerrainEdge_hpp */
