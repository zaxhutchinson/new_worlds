#include"vec3i.hpp"

Vec3i::Vec3i() : x(0), y(0), z(0) {}
Vec3i::Vec3i(i64 _x, i64 _y, i64 _z)
    : x(_x), y(_y), z(_z)
{}

i64 Vec3i::X() const { return x; }
i64 Vec3i::Y() const { return y; }
i64 Vec3i::Z() const { return z; }
void Vec3i::X(i64 _x) { x = _x; }
void Vec3i::Y(i64 _y) { y = _y; }
void Vec3i::Z(i64 _z) { z = _z; }


bool Vec3i::operator==(const Vec3i & v) const {
    return x==v.x && y==v.y && z==v.z;
}
bool Vec3i::operator!=(const Vec3i & v) const {
    return !(*this==v);
}
Vec3i & Vec3i::operator+=(const Vec3i & v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}