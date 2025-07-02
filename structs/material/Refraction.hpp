#ifndef LAB3A_REFRACTION_HPP
#define LAB3A_REFRACTION_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Refraction {
    float iof{};

    explicit Refraction(const pugi::xml_node &node) :
            iof{node.attribute("iof").as_float()} {}
};

#endif
