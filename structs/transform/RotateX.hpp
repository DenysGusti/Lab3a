#ifndef LAB3A_ROTATEX_HPP
#define LAB3A_ROTATEX_HPP

#include "ITransform.hpp"
#include "Rotate.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct RotateX : ITransform {
    Rotate rotateX;

    explicit RotateX(const pugi::xml_node &node) :
            rotateX{node.child("rotateX")} {}
};

#endif
