#ifndef TerrainVertex_hpp
#define TerrainVertex_hpp

#include "mt.hpp"
#include "Geometry.hpp"

namespace mt {
namespace exst {

class TerrainEdge;
class TerrainVertex {
public:
    friend class Terrain;
    virtual ~TerrainVertex() { }
    TerrainVertex(const Coordinate & pos);
    
    Coordinate position() const;
    shared_ptr<TerrainEdge> edge1() const;
    shared_ptr<TerrainEdge> edge2() const;
    
private:
    Coordinate m_pos;
    shared_ptr<TerrainEdge> m_e1 = nullptr;
    shared_ptr<TerrainEdge> m_e2 = nullptr;
};

}
}

#endif /* TerrainVertex_hpp */
