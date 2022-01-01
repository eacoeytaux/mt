#ifndef Terrain_hpp
#define Terrain_hpp

#include "mt.hpp"
#include "Graphics.hpp"
#include "Object.hpp"
#include "TerrainVertex.hpp"
#include "TerrainEdge.hpp"

namespace mt {
namespace exst {

class Terrain : public Object {
public:
    Terrain(World*);
    
    const varray<shared_ptr<TerrainVertex>> & vertices() const;
    const varray<shared_ptr<TerrainEdge>> & edges() const;
    
    void update();
    void draw(const Camera *) const;
    
private:
    varray<shared_ptr<TerrainVertex>> m_vertices;
    varray<shared_ptr<TerrainEdge>> m_edges;
};

}
}

#endif /* Terrain_hpp */
