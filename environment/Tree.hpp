#ifndef Tree_hpp
#define Tree_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exists {

class Tree : public Object {
public:
    Tree(World*, const Coordinate & root);
    
    void draw(const Camera *) const;
};

}
}

#endif /* Tree_hpp */
