#ifndef LAB3A_PARALLELLIGHT_HPP
#define LAB3A_PARALLELLIGHT_HPP

#include "ALight.hpp"

struct ParallelLight : ALight {
    Vec3 direction;

    Vec3 lightVector;

    explicit ParallelLight(const pugi::xml_node &node) :
            ALight{node},
            direction{node.child("direction")},
            lightVector{-direction.normalized()} {}

    [[nodiscard]] Vec3 getLightVector(const Vec3 &point) const override {
        return lightVector;
    }

    [[nodiscard]] Vec3 getPosition() const override {
        return {numeric_limits<float>::infinity(),
                numeric_limits<float>::infinity(),
                numeric_limits<float>::infinity()};
    }
};

#endif
