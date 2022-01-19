#ifndef BackgroundTerrain_hpp
#define BackgroundTerrain_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class BackgroundTerrain
/// @brief non-interactable background terrain (visual only)
class BackgroundTerrain : public Object {
public:
    virtual ~BackgroundTerrain() { }
    BackgroundTerrain(World *, float z);
    
    void update(float dt) override;
    void draw(const Camera *) const override;
    
private:
    
};

}
}

#endif /* BackgroundTerrain_hpp */
