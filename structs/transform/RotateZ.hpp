#ifndef LAB3A_ROTATEZ_HPP
#define LAB3A_ROTATEZ_HPP

#include "ITransform.hpp"
#include "Rotate.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct RotateZ : ITransform {
    Rotate rotateZ;

    explicit RotateZ(const pugi::xml_node &node) :
            rotateZ{node} {}
};

#endif
