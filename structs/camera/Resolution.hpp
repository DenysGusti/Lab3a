#ifndef LAB3A_RESOLUTION_HPP
#define LAB3A_RESOLUTION_HPP

#include <cmath>

#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct Resolution {
    uint64_t horizontal{};
    uint64_t vertical{};

    float reciprocalHorizontal{};
    float reciprocalVertical{};

    explicit Resolution(const pugi::xml_node &node) :
            horizontal{node.attribute("horizontal").as_ullong()},
            vertical{node.attribute("vertical").as_ullong()},
            reciprocalHorizontal{1.f / static_cast<float>(horizontal)},
            reciprocalVertical{1.f / static_cast<float>(vertical)} {}

    [[nodiscard]] float aspectRatio() const {
        return static_cast<float>(vertical) / static_cast<float>(horizontal);
    }
};

#endif
