#include "Joint.hpp"

NAMESPACES
using mt::util::Joint;

Joint::Joint(const Coordinate & _c1, float _arm_length_1, float _arm_length_2, const Coordinate & _c2, bool _inward) :
m_c1(_c1),
m_c2(_c2),
m_arm_length_1(_arm_length_1),
m_arm_length_2(_arm_length_2),
m_inward(_inward) {
    float distance = m_c1.distance(m_c2);
    Assert::fatal(in_range(distance, m_arm_length_1 + m_arm_length_2, m_arm_length_1 - m_arm_length_2), "joint is impossible");
}

Coordinate Joint::c1() const {
    return m_c1;
}

Coordinate Joint::c2() const {
    return m_c2;
}

Coordinate Joint::joint() const {
    float a = m_c1.distance(m_c2);
    float b = m_arm_length_1;
    float c = m_arm_length_2;
    
    Angle arm_1_angle = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
    if (m_inward) arm_1_angle *= -1;
    arm_1_angle += Vector(m_c1, m_c2).angle();
    return Vector(arm_1_angle, m_arm_length_1).origin(m_c1).destination();
}

float Joint::arm_length_1() const {
    return m_arm_length_2;
}

float Joint::arm_length_2() const {
    return m_arm_length_2;
}
