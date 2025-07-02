#ifndef LAB3A_TEXTURE_HPP
#define LAB3A_TEXTURE_HPP

#include <string>

#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct Texture {
    string name;

    explicit Texture(const pugi::xml_node &node) :
            name{node.attribute("name").as_string()} {}
};

#endif
