#ifndef LAB3A_POINTLIGHT_HPP
#define LAB3A_POINTLIGHT_HPP

#include "ALight.hpp"

struct PointLight : ALight {
    Vec3 position;

    explicit PointLight(const pugi::xml_node &node) :
            ALight{node},
            position{node.child("position")} {}

    [[nodiscard]] Vec3 getLightVector(const Vec3 &point) const override {
        return (position - point).normalized();
    }

    [[nodiscard]] Vec3 getPosition() const override {
        return position;
    }
};

#endif
