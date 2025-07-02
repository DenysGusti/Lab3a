#ifndef LAB3A_ALIGHT_HPP
#define LAB3A_ALIGHT_HPP

#include "../math/Vec3.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct ALight {
    Vec3 color;

    virtual ~ALight() = default;

    explicit ALight(const pugi::xml_node &node) :
            color{node.child("color")} {}

    [[nodiscard]] virtual Vec3 getLightVector(const Vec3 &point) const = 0;

    [[nodiscard]] virtual Vec3 getPosition() const = 0;
};

#endif
