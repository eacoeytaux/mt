#ifndef Joint_hpp
#define Joint_hpp

#include "mt.hpp"
#include "geometry.hpp"

namespace mt {
namespace util {

/// @class Joint
/// @brief template file
class Joint {
public:
    virtual ~Joint() { }
    Joint(const Coordinate & c1, float arm_length_1, float arm_length_2, const Coordinate & c2, bool inward = true);
    
    Coordinate c1() const;
    Coordinate c2() const;
    Coordinate joint() const;
    float arm_length_1() const;
    float arm_length_2() const;
    
private:
    Coordinate m_c1;
    Coordinate m_c2;
    float m_arm_length_1;
    float m_arm_length_2;
    bool m_inward;
};

}
}

#endif /* Joint_hpp */
