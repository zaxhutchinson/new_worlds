#include"vec2i.hpp"


Vec2i::Vec2i() 
    :x(0), y(0)
{}
Vec2i::Vec2i(i64 _x, i64 _y) 
    :x(_x), y(_y)
{}

bool Vec2i::operator==(const Vec2i & o) const {
    return x==o.x && y==o.y;
}
bool Vec2i::operator!=(const Vec2i & o) const {
    return !(*this==o);
}
Vec2i & Vec2i::operator+=(const Vec2i & o) {
    x += o.x;
    y += o.y;
    return *this;
}

i64 Vec2i::X() const { return x; }
i64 Vec2i::Y() const { return y; }
void Vec2i::X(i64 _x) { x = _x; }
void Vec2i::Y(i64 _y) { y = _y; }

i64 Vec2i::DistanceMan(const Vec2i & o) const {
    return std::abs(x-o.x) + std::abs(y-o.y);
}
double Vec2i::DistanceStrLine(const Vec2i & o) const {
    return std::sqrt(
        std::pow(x-o.x, 2.0) +
        std::pow(y-o.y, 2.0)
    );
}