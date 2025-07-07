#ifndef LAB3A_ASURFACE_HPP
#define LAB3A_ASURFACE_HPP

#include <optional>
#include <memory>
#include <vector>
#include <exception>
#include <iostream>
#include <cmath>

#include "../math/Vec3.hpp"
#include "../material/AMaterial.hpp"
#include "../material/MaterialSolid.hpp"
#include "../material//MaterialTextured.hpp"
#include "../transform/ITransform.hpp"
#include "../transform/Translate.hpp"
#include "../transform/Scale.hpp"
#include "../transform/RotateX.hpp"
#include "../transform/RotateY.hpp"
#include "../transform/RotateZ.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"
#include "../geometry/Ray.hpp"
#include "../geometry/HitInfo.hpp"

using namespace std;

struct ASurface {
    unique_ptr<AMaterial> material;
    vector<unique_ptr<ITransform> > transforms;

    virtual ~ASurface() = default;

    explicit ASurface(const pugi::xml_node &node) {
        if (const auto material_solid_node = node.child("material_solid"))
            material = make_unique<MaterialSolid>(material_solid_node);
        else if (const auto material_textured_node = node.child("material_textured"))
            material = make_unique<MaterialTextured>(material_textured_node);
        else {
            cerr << "Surface is missing a valid <material_solid> or <material_textured> child." << endl;
            throw invalid_argument{"Surface is missing a child."};
        }

        if (const auto transform_node = node.child("transform"))
            for (const auto &t: transform_node.children()) {
                string_view type = t.name();

                if (type == "translate")
                    transforms.push_back(make_unique<Translate>(t));
                else if (type == "scale")
                    transforms.push_back(make_unique<Scale>(t));
                else if (type == "rotateX")
                    transforms.push_back(make_unique<RotateX>(t));
                else if (type == "rotateY")
                    transforms.push_back(make_unique<RotateY>(t));
                else if (type == "rotateZ")
                    transforms.push_back(make_unique<RotateZ>(t));
                else {
                    cerr << "Unknown transform type: " << type << endl;
                    throw invalid_argument{"Unknown transform type."};
                }
            }
    }

    [[nodiscard]] virtual optional<HitInfo> hit(const Ray &ray) const = 0;
};

#endif
