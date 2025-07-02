#ifndef LAB3A_MATERIALSOLID_HPP
#define LAB3A_MATERIALSOLID_HPP

#include "AMaterial.hpp"

struct MaterialSolid : AMaterial {
    Vec3 color;

    explicit MaterialSolid(const pugi::xml_node &node) :
            AMaterial{node},
            color{node.child("color")} {}

    [[nodiscard]] Vec3 getColor() const override {
        return color;
    }
};

#endif
