#ifndef LAB3A_SCENE_HPP
#define LAB3A_SCENE_HPP

#include <string>
#include <iostream>

#include "camera/Camera.hpp"
#include "light/ALight.hpp"
#include "light/AmbientLight.hpp"
#include "light/PointLight.hpp"
#include "light/ParallelLight.hpp"
#include "light/SpotLight.hpp"
#include "surface/ASurface.hpp"
#include "surface/Sphere.hpp"
#include "surface/Mesh.hpp"
#include "../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct Scene {
    static constexpr uint64_t CHANNELS = 3;
    static constexpr float SHADOW_EPSILON = 0.0005f;

    string output_file;
    Vec3 background_color;
    Camera camera;
    vector<unique_ptr<ALight> > lights;
    vector<unique_ptr<ASurface> > surfaces;

    explicit Scene(const pugi::xml_node &node)
            : output_file{node.attribute("output_file").as_string()},
              background_color{node.child("background_color")},
              camera{node.child("camera")} {

        const auto surfaces_node = node.child("surfaces");
        for (const auto &surface_node: surfaces_node.children()) {
            string_view type = surface_node.name();

            if (type == "sphere")
                surfaces.push_back(make_unique<Sphere>(surface_node));
            else if (type == "mesh")
                surfaces.push_back(make_unique<Mesh>(surface_node));
            else
                cout << "Unknown surface type: " << type;
        }

        const auto lights_node = node.child("lights");
        for (const auto &light_node: lights_node.children()) {
            string_view type = light_node.name();

            if (type == "ambient_light")
                lights.push_back(make_unique<AmbientLight>(light_node));
            else if (type == "point_light")
                lights.push_back(make_unique<PointLight>(light_node));
            else if (type == "parallel_light")
                lights.push_back(make_unique<ParallelLight>(light_node));
            else if (type == "spot_light")
                lights.push_back(make_unique<SpotLight>(light_node));
            else
                cout << "Unknown light type: {}" << type;
        }
    }

    [[nodiscard]] vector<uint8_t> raytracing() const {
        const uint64_t imageHeight = camera.resolution.vertical;
        const uint64_t imageWidth = camera.resolution.horizontal;

        vector<uint8_t> pixels(CHANNELS * imageWidth * imageHeight);

        for (uint64_t y = 0; y < imageHeight; ++y) {
            for (uint64_t x = 0; x < imageWidth; ++x) {
                const size_t flippedY = imageHeight - 1 - y;
                const size_t idx = CHANNELS * (flippedY * imageWidth + x);

                const Ray ray = camera.getRayToPixel(x, y);
                Vec3 color = traceRayColor(ray);

                const array<uint8_t, 3> bytes = color.toBytes();
                for (size_t i = 0; i < bytes.size(); ++i)
                    pixels[idx + i] = bytes[i];
            }
            printProgressBar(static_cast<float>(y + 1) / static_cast<float>(imageHeight));
        }
        cout << '\n';
        return pixels;
    }

    [[nodiscard]] Vec3 traceRayColor(const Ray &ray) const {
        const optional<HitInfo> hit = getClosestHit(ray);
        if (!hit)
            return background_color;

        Vec3 color;
        for (const auto &light: lights) {
            const Vec3 lightVector = light->getLightVector(hit->point);
            const float maxDistance = (light->getPosition() - hit->point).length();

            const Ray shadowRay{hit->point, lightVector, SHADOW_EPSILON, maxDistance};
            if (lightVector.zero() || !hitAnything(shadowRay))
                color += hit->material->illuminate(-ray.direction, hit->normal, lightVector, light->color);
        }
        return color;
    }

    [[nodiscard]] optional<HitInfo> getClosestHit(const Ray &ray) const {
        pair<float, HitInfo> closestHit{numeric_limits<float>::infinity(), {}};
        for (const auto &surface: surfaces) {
            const optional<HitInfo> hitInfo = surface->hit(ray);

            if (hitInfo && hitInfo->t < closestHit.first && ray.contains(hitInfo->t))
                closestHit = {hitInfo->t, *hitInfo};
        }

        if (isinf(closestHit.first))
            return nullopt;
        return {closestHit.second};
    }

    [[nodiscard]] bool hitAnything(const Ray &ray) const {
        for (const auto &surface: surfaces) {
            const optional<HitInfo> hitInfo = surface->hit(ray);
            if (hitInfo && ray.contains(hitInfo->t))
                return true;
        }
        return false;
    }

    static void printProgressBar(const float progress) {
        const size_t barWidth = 50;
        const uint64_t pos = static_cast<int>(barWidth * progress);

        string bar;
        bar.reserve(barWidth + 20);

        bar += "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos)
                bar += "=";
            else if (i == pos)
                bar += ">";
            else
                bar += " ";
        }
        bar += "] " + to_string(static_cast<uint64_t>(progress * 100.f)) + '%';

        cout << bar << flush;
    }
};

#endif
