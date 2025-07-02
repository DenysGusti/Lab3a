#ifndef LAB3A_SCALE_HPP
#define LAB3A_SCALE_HPP

#include "ITransform.hpp"
#include "../math/Vec3.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct Scale : ITransform {
    Vec3 scale;

    explicit Scale(const pugi::xml_node &node) :
            scale{node.child("scale")} {}
};

#endif
