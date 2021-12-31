#ifndef Namespaces_hpp
#define Namespaces_hpp

/// @brief top level namespace
namespace mt {

/// @brief utility functions and classes
namespace util { }
/// @brief basic geometry classes
namespace geometry { }
/// @brief everything graphics
namespace graphics { }
/// @brief basic physic classes
namespace physics { }
/// @brief things that exist in reality
namespace exists { }

//using namespace mt;
//using namespace mt::util;
//using namespace mt::geometry;
//using namespace mt::graphics;
//using namespace mt::physics;
//using namespace mt::exists;

#define NAMESPACES using namespace mt; using namespace mt::util; using namespace mt::geometry; using namespace mt::graphics; using namespace mt::physics; using namespace mt::exists;
NAMESPACES

}

#endif /* Namespaces_hpp */
