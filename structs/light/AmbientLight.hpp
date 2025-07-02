#ifndef LAB3A_AMBIENTLIGHT_HPP
#define LAB3A_AMBIENTLIGHT_HPP

#include "ALight.hpp"

struct AmbientLight : ALight {
    explicit AmbientLight(const pugi::xml_node &node) : ALight{node} {}

    [[nodiscard]] Vec3 getLightVector(const Vec3 &point) const override {
        return {0, 0, 0};
    }

    [[nodiscard]] Vec3 getPosition() const override {
        return {numeric_limits<float>::infinity(),
                numeric_limits<float>::infinity(),
                numeric_limits<float>::infinity()};
    }
};

#endif
