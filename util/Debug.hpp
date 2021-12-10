#ifndef Debug_hpp
#define Debug_hpp

#define MT_DEBUG

namespace mt {

#ifdef MT_DEBUG
class Debug {
public:
    static bool on;
};
#endif
    
}

#endif /* Debug_hpp */
