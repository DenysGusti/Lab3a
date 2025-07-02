#ifndef LAB3A_MESH_HPP
#define LAB3A_MESH_HPP

#include <string>
#include <memory>
#include <vector>

#include "ASurface.hpp"

using namespace std;

struct Mesh : ASurface {
    string name;

    explicit Mesh(const pugi::xml_node &node) :
            ASurface{node},
            name{node.attribute("name").as_string()} {}

    [[nodiscard]] optional<HitInfo> hit(const Ray &ray) const override {
        cout << "Mesh not implemented yet.\n";
        return nullopt;
    }
};

#endif
