#ifndef TerrainVertex_hpp
#define TerrainVertex_hpp

#include "geometry.hpp"

namespace mt {

class TerrainEdge;
class TerrainVertex {
public:
    friend class TerrainEdge;
    TerrainVertex(const Coordinate & pos);
    
    Coordinate position() const;
    TerrainEdge * edge1() const;
    TerrainEdge * edge2() const;
    
private:
    Coordinate m_pos;
    TerrainEdge * m_e1 = nullptr;
    TerrainEdge * m_e2 = nullptr;
};

}

#endif /* TerrainVertex_hpp */
