#ifndef Random_hpp
#define Random_hpp

#include "SysIncludes.hpp"

namespace mt {

namespace geometry { class Angle; }
namespace graphics { class Color; }

namespace util {

/// @class Random
/// @brief interface for all RNG
class Random {
public:
    /// @brief seed with current time
    static bool seed();
    /// @brief seed with specified seed
    /// @param seed RNG seed
    static bool seed(unsigned int seed);
    /// @brief random bool
    /// @param true_odds how likely a value of true is, 0 = no chance, 1 = guaranteed, default 0.5
    /// @return boolean with ( true_odds ) chance of true and ( 1 - true_odds ) chance of false
    static bool r_bool(float true_odds = 0.5);
    /// @brief random Angle
    /// @return random Angle in range [0, 2*pi)
    static geometry::Angle r_Angle();
    /// @brief random int
    /// @return random int in range [0, range)
    static int r_int(int range);
    /// @brief random int
    /// @return random int in range [low_bound, high_bound)
    static int r_int(int low_bound, int high_bound);
    /// @brief random float
    /// @return random float in range [0, range)
    static float r_float(float range);
    /// @brief random float
    /// @return random float in range [low_bound, high_bound)
    static float r_float(float low_bound, float high_bound);
    /// @brief random color
    /// @return random color
    static Color r_Color();
    
private:
    /// @brief should never be constructed
    Random() { }
};

}
}

#endif /* Random_hpp */
