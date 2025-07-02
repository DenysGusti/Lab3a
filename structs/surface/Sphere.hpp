#ifndef LAB3A_SPHERE_HPP
#define LAB3A_SPHERE_HPP

#include "ASurface.hpp"

using namespace std;

struct Sphere : ASurface {
    float radius{};
    Vec3 position;

    explicit Sphere(const pugi::xml_node &node) :
            ASurface{node},
            radius{node.attribute("radius").as_float()},
            position{node.child("position")} {}

    [[nodiscard]] optional<HitInfo> hit(const Ray &ray) const override {
        const Vec3 oc = ray.origin - position;
        const float a = ray.direction.lengthSquared();
        const float b = ray.direction.dot(oc);
        const float c = oc.lengthSquared() - radius * radius;
        const float d = b * b - a * c;

        if (d < 0)
            return nullopt;

        const float sqrt_d = sqrt(d);
        float t = (-b - sqrt_d) / a;
        if (!ray.contains(t)) {
            t = (-b + sqrt_d) / a;
            if (!ray.contains(t))
                return nullopt;
        }

        const Vec3 point = ray.getPoint(t);
        const Vec3 normal = (point - position) / radius;

        return HitInfo{t, point, normal, material.get()};
    }
};

#endif
