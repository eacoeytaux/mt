#ifndef TerrainEdge_hpp
#define TerrainEdge_hpp

#include "mt.hpp"
#include "geometry.hpp"

namespace mt {

class TerrainVertex;
class TerrainEdge {
public:
//    friend class TerrainVertex;
    TerrainEdge(shared_ptr<TerrainVertex> v1, shared_ptr<TerrainVertex> v2);
    TerrainEdge(const TerrainEdge &);
    
    Line line() const;
    TerrainVertex * vertex1() const;
    TerrainVertex * vertex2() const;
    
private:
    TerrainVertex * m_v1 = nullptr;
    TerrainVertex * m_v2 = nullptr;
};

}

#endif /* TerrainEdge_hpp */
