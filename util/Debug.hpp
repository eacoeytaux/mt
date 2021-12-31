#ifndef Debug_hpp
#define Debug_hpp

#define MT_DEBUG

namespace mt {
namespace util {

#ifdef MT_DEBUG
/// @class Debug
/// @brief all debugging
class Debug {
public:
    static bool on;
};
#endif
    
}
}

#endif /* Debug_hpp */
