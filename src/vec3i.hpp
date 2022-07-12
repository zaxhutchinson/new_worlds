#pragma once

#include<cmath>

#include"zxlb.hpp"

class Vec3i {
private:
    i64 x;
    i64 y;
    i64 z;
public:
    Vec3i();
    Vec3i(i64 _x, i64 _y, i64 _z);
    Vec3i(const Vec3i & v) = default;
    Vec3i(Vec3i && v) = default;
    Vec3i& operator=(const Vec3i & v) = default;
    Vec3i& operator=(Vec3i && v) = default;

    bool operator==(const Vec3i & v) const;
    bool operator!=(const Vec3i & v) const;
    Vec3i & operator+=(const Vec3i & v);

    i64 X() const;
    i64 Y() const;
    i64 Z() const;
    void X(i64 _x);
    void Y(i64 _y);
    void Z(i64 _z);
};


namespace std
{
    template <>
    struct hash<Vec3i>
    {
        size_t operator()( const Vec3i& k ) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<i64>()( k.X() );
            res = res * 31 + hash<i64>()( k.Y() );
            res = res * 31 + hash<i64>()( k.Z() );
            return res;
        }
    };
}