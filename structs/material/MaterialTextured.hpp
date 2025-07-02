#ifndef LAB3A_MATERIALTEXTURED_HPP
#define LAB3A_MATERIALTEXTURED_HPP

#include "AMaterial.hpp"
#include "Texture.hpp"

struct MaterialTextured : AMaterial {
    Texture texture;

    explicit MaterialTextured(const pugi::xml_node &node) :
            AMaterial{node},
            texture{node.child("texture")} {}

    [[nodiscard]] Vec3 getColor() const override {
        cout << "getColor is not implemented yet for MaterialTextured\n";
        return {1, 1, 1};
    }
};

#endif
