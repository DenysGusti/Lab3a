#ifndef LAB3A_AMATERIAL_HPP
#define LAB3A_AMATERIAL_HPP

#include "Phong.hpp"
#include "Reflectance.hpp"
#include "Transmittance.hpp"
#include "Refraction.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"
#include "../math/Vec3.hpp"

struct AMaterial {
    Phong phong;
    Reflectance reflectance;
    Transmittance transmittance;
    Refraction refraction;

    virtual ~AMaterial() = default;

    explicit AMaterial(const pugi::xml_node &node) :
            phong{node.child("phong")},
            reflectance{node.child("reflectance")},
            transmittance{node.child("transmittance")},
            refraction{node.child("refraction")} {}

    [[nodiscard]] virtual Vec3 getColor() const = 0;

    [[nodiscard]] Vec3 illuminate(const Vec3 &V, const Vec3 &N, const Vec3 &L, const Vec3 &lightColor) const {
        const Vec3 materialColor = getColor();

        // ambient light is handled separately
        if (L.zero()) {
            const Vec3 ambientColor = lightColor * materialColor * phong.ka;
            return ambientColor;
        }

        const float diffuseIntensity = max(N.dot(L), 0.f);
        if (diffuseIntensity == 0)
            return {0, 0, 0};

        const Vec3 diffuseColor = lightColor * materialColor * diffuseIntensity * phong.kd;

        const float specularIntensity = computePhongSpecularIntensity(V, N, L);
        if (specularIntensity == 0)
            return diffuseColor;

        const Vec3 specularColor = lightColor * specularIntensity * phong.ks;

        return diffuseColor + specularColor;
    }

    [[nodiscard]] float computePhongSpecularIntensity(const Vec3 &V, const Vec3 &N, const Vec3 &L) const {
        const Vec3 R = -L.reflect(N);    // reflection vector 2. * dot(N, L) * N - L

        const float RdotV = max(R.dot(V), 0.f);

        return pow(RdotV, phong.exponent);
    }
};

#endif
