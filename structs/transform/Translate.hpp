#ifndef LAB3A_TRANSLATE_HPP
#define LAB3A_TRANSLATE_HPP

#include "ITransform.hpp"
#include "../math/Vec3.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct Translate : ITransform {
    Vec3 translate;

    explicit Translate(const pugi::xml_node &node) :
            translate{node} {}
};

#endif
