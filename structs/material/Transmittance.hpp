#ifndef LAB3A_TRANSMITTANCE_HPP
#define LAB3A_TRANSMITTANCE_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Transmittance {
    float t{};

    explicit Transmittance(const pugi::xml_node &node) :
            t{node.attribute("t").as_float()} {}
};

#endif
