#ifndef LAB3A_SPOTLIGHT_HPP
#define LAB3A_SPOTLIGHT_HPP

#include "ALight.hpp"
#include "Falloff.hpp"

struct SpotLight : ALight {
    Vec3 position;
    Vec3 direction;
    Falloff falloff;

    explicit SpotLight(const pugi::xml_node &node) :
            ALight{node},
            position{node.child("position")},
            direction{node.child("position")},
            falloff{node.child("falloff")} {}

    [[nodiscard]] Vec3 getLightVector(const Vec3 &point) const override {
        return (position - point).normalized();
        // TODO intensity
    }

    [[nodiscard]] Vec3 getPosition() const override {
        return position;
    }
};

#endif
