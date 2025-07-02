#ifndef LAB3A_RAY_HPP
#define LAB3A_RAY_HPP

#include <numeric>

#include "../math/Vec3.hpp"

struct Ray {
    Vec3 origin;
    Vec3 direction;
    float t_min{};
    float t_max{};

    Ray() = default;

    Ray(const Vec3 &origin_, const Vec3 &direction_,
        const float t_min_ = 0, const float t_max = numeric_limits<float>::infinity()) :
            origin{origin_},
            direction{direction_.normalized()},
            t_min{t_min_},
            t_max{t_max} {}

    [[nodiscard]] inline bool contains(const float t) const {
        return t_min <= t && t <= t_max;
    }

    [[nodiscard]] inline Vec3 getPoint(const float t) const {
        return origin + direction * t;
    }
};

#endif
