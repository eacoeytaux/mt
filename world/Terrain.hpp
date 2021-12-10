#ifndef Terrain_hpp
#define Terrain_hpp

#include "Visible.hpp"
#include "TerrainVertex.hpp"
#include "TerrainEdge.hpp"

namespace mt {

class Terrain : public Visible {
public:
    Terrain();
    
    const varray<shared_ptr<TerrainVertex>> & vertices() const;
    const varray<shared_ptr<TerrainEdge>> & edges() const;
    
    void draw(const Camera &) const;
    
private:
    varray<shared_ptr<TerrainVertex>> m_vertices;
    varray<shared_ptr<TerrainEdge>> m_edges;
};

}

#endif /* Terrain_hpp */
