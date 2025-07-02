#ifndef LAB3A_HORIZONTALFOV_HPP
#define LAB3A_HORIZONTALFOV_HPP

#include <numbers>

#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct HorizontalFov {
    float angle{};

    explicit HorizontalFov(const pugi::xml_node &node) :
            angle{node.attribute("angle").as_float()} {}

    [[nodiscard]] float radians() const {
        return angle * numbers::pi_v<float> / 180.f;
    }
};

#endif
