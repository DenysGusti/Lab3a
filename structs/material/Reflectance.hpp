#ifndef LAB3A_REFLECTANCE_HPP
#define LAB3A_REFLECTANCE_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Reflectance {
    float r;

    explicit Reflectance(const pugi::xml_node &node) :
            r{node.attribute("r").as_float()} {}
};

#endif
