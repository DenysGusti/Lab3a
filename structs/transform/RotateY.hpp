#ifndef LAB3A_ROTATEY_HPP
#define LAB3A_ROTATEY_HPP

#include "ITransform.hpp"
#include "Rotate.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

struct RotateY : ITransform {
    Rotate rotateY;

    explicit RotateY(const pugi::xml_node &node) :
            rotateY{node} {}
};

#endif
