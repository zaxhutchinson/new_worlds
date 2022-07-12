#pragma once

#include<cmath>

#include"zxlb.hpp"

class Vec2i {

private:
    i64 x;
    i64 y;

public:
    Vec2i();
    Vec2i(i64 _x, i64 _y);
    Vec2i(const Vec2i & v) = default;
    Vec2i(Vec2i && v) = default;
    Vec2i& operator=(const Vec2i & v) = default;
    Vec2i& operator=(Vec2i && v) = default;

    bool operator==(const Vec2i & o) const;
    bool operator!=(const Vec2i & o) const;
    Vec2i & operator+=(const Vec2i & o);

    i64 X() const;
    i64 Y() const;
    void X(i64 _x);
    void Y(i64 _y);

    i64 DistanceMan(const Vec2i & o) const;
    double DistanceStrLine(const Vec2i & o) const;
};



namespace std
{
    template <>
    struct hash<Vec2i>
    {
        size_t operator()( const Vec2i& k ) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<i64>()( k.X() );
            res = res * 31 + hash<i64>()( k.Y() );
            return res;
        }
    };
}