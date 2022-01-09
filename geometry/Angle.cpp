#include "Angle.hpp"

#include "Vector.hpp"

NAMESPACES
using mt::geometry::Angle;

Angle::Angle(const float _radians, const bool _truncate) {
    truncate(_truncate);
    radians(_radians);
}

Angle::Angle(const float _dx, const float _dy, const bool _truncate) {
    truncate(_truncate);
    radians(atan2(_dy, _dx));
}

bool Angle::truncating() const {
    return m_truncate;
}

Angle & Angle:: truncate(const bool _truncate) {
    m_truncate = _truncate;
    return *this;
}

float Angle::radians() const {
    return m_radians;
}

float Angle::degrees() const {
    return (radians() / PI) * 180.0;
}

Angle & Angle::radians(const float _radians) {
    float radians = _radians;
    if ((_radians == POS_INFINITY) || (_radians == NEG_INFINITY)) radians = 0;
    if (truncating()) {
        radians -= floor(radians / (PI * 2)) * (PI * 2);
//        while (radians > (PI * 2))
//            radians -= (PI * 2);
//        while (radians < 0)
//            radians += (PI * 2);
    }
    m_radians = radians;
#ifdef MT_DEBUG
    m_degrees = radians_to_degrees(radians);
#endif
    return *this;
}

Angle & Angle::radians(const float _dx, const float _dy) {
    radians(atan2(_dy, _dx));
    return *this;
}

float Angle::sin(const float _multiplier) const {
    return ::sin(radians()) * _multiplier;
}

float Angle::cos(const float _multiplier) const {
    return ::cos(radians()) * _multiplier;
}

QUADRANT Angle::quadrant() const {
    return Vector(*this, 1).destination().quadrant();
}

AXIS Angle::axis() const {
    return Vector(*this, 1).destination().axis();
}

bool Angle::in_quadrant(const QUADRANT _quadrant) const {
    return quadrant() == _quadrant;
}

bool Angle::on_axis(const AXIS _axis) const {
    return axis() == _axis;
}

Angle Angle::operator+(const Angle & _angle) const {
    return Angle(radians() + _angle.radians());
}

Angle & Angle::operator+=(const Angle & _angle) {
    radians(radians() + _angle.radians());
    return *this;
}

Angle Angle::operator-(const Angle & _angle) const {
    return Angle(radians() - _angle.radians());
}

Angle & Angle::operator-=(const Angle & _angle) {
    radians(radians() - _angle.radians());
    return *this;
}

Angle & Angle::operator=(const float _radians) {
    radians(_radians);
    return *this;
}

Angle Angle::operator+(float _radians) const {
    return Angle(radians() + _radians);
}

Angle & Angle::operator+=(float _radians) {
    radians(radians() + _radians);
    return *this;
}

Angle Angle::operator-(float _radians) const {
    return Angle(radians() - _radians);
}

Angle & Angle::operator-=(float _radians) {
    radians(radians() - _radians);
    return *this;
}

Angle Angle::operator*(float _scale) const {
    return Angle(radians() * _scale);
}

Angle & Angle::operator*=(float _scale) {
    radians(radians() * _scale);
    return *this;
}

Angle Angle::operator/(float _scale) const {
    return Angle(radians() / _scale);
}

Angle & Angle::operator/=(float _scale) {
    radians(radians() / _scale);
    return *this;
}

bool Angle::operator==(const Angle & _angle) const {
    return float_eq(radians(), _angle.radians());
}

bool Angle::operator!=(const Angle & _angle) const {
    return !(*this == _angle);
}

bool Angle::operator>(const Angle & _angle) const {
    return float_gt(radians(), _angle.radians());
}

bool Angle::operator>=(const Angle & _angle) const {
    return float_ge(radians(), _angle.radians());
}

bool Angle::operator<(const Angle & _angle) const {
    return float_lt(radians(), _angle.radians());
}

bool Angle::operator<=(const Angle & _angle) const {
    return float_le(radians(), _angle.radians());
}

float Angle::radians_to_degrees(const float _radians) {
    return _radians * 180 / PI;
}

float Angle::degrees_to_radians(const float _degrees) {
    return _degrees * PI / 180;
}
