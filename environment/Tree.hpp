#ifndef Tree_hpp
#define Tree_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

class Tree : public Object {
public:
    virtual ~Tree() { }
    Tree(World *, const Coordinate & root);
    
    void draw(const Camera *) const;
};

}
}

#endif /* Tree_hpp */
