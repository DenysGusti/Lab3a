#ifndef LAB3A_MAXBOUNCES_HPP
#define LAB3A_MAXBOUNCES_HPP

#include <cmath>

#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct MaxBounces {
    uint64_t n{};

    explicit MaxBounces(const pugi::xml_node &node) :
            n{node.attribute("n").as_ullong()} {}
};

#endif
