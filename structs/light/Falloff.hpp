#ifndef LAB3A_FALLOFF_HPP
#define LAB3A_FALLOFF_HPP

#include "../../libs/pugixml/src/pugixml.hpp"

struct Falloff {
    float alpha1{};
    float alpha2{};

    explicit Falloff(const pugi::xml_node &node) :
            alpha1{node.attribute("alpha1").as_float()},
            alpha2{node.attribute("alpha2").as_float()} {}
};

#endif
