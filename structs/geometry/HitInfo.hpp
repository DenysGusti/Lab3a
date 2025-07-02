#ifndef LAB3A_HITINFO_HPP
#define LAB3A_HITINFO_HPP

#include "../math/Vec3.hpp"
#include "../material/AMaterial.hpp"

struct HitInfo {
    float t{};
    Vec3 point;
    Vec3 normal;
    const AMaterial *material{};

    HitInfo() = default;

    HitInfo(const float t_, const Vec3 &point_, const Vec3 &normal_, const AMaterial *const material_) :
            t{t_}, point{point_}, normal{normal_}, material{material_} {}
};

#endif
