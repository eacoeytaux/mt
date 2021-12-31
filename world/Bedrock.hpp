#ifndef Bedrock_hpp
#define Bedrock_hpp

#include "mt.hpp"
#include "Terrain.hpp"

namespace mt {
namespace exists {

class Bedrock : public Terrain {
public:
    Bedrock();
    
    virtual void draw(const Camera *) const override; // todo add more overrides
    
    virtual varray<Line> camera_buffer(const Camera *) const;
};

}
}

#endif /* Bedrock_hpp */
