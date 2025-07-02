#ifndef LAB3A_PHONG_HPP
#define LAB3A_PHONG_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Phong {
    float ka{};
    float kd{};
    float ks{};
    float exponent{};

    explicit Phong(const pugi::xml_node &node) :
            ka{node.attribute("ka").as_float()},
            kd{node.attribute("kd").as_float()},
            ks{node.attribute("ks").as_float()},
            exponent{node.attribute("exponent").as_float()} {}
};

#endif
