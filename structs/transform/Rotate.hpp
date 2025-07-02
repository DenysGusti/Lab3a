#ifndef LAB3A_ROTATE_HPP
#define LAB3A_ROTATE_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Rotate {
    float theta{};

    explicit Rotate(const pugi::xml_node &node) :
            theta{node.attribute("theta").as_float()} {}
};

#endif
