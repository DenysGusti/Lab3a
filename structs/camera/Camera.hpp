#ifndef LAB3A_CAMERA_HPP
#define LAB3A_CAMERA_HPP

#include <cmath>

#include "../math/Vec3.hpp"
#include "../geometry/Ray.hpp"
#include "../math/Mat4.hpp"
#include "HorizontalFov.hpp"
#include "Resolution.hpp"
#include "MaxBounces.hpp"
#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct Camera {
    Vec3 position;
    Vec3 lookat;
    Vec3 up;
    HorizontalFov horizontal_fov;
    Resolution resolution;
    MaxBounces max_bounces;

    float tan_fov_x{};
    float tan_fov_y{};
    Mat4 lookAt;

    explicit Camera(const pugi::xml_node &node) :
            position{node.child("position")},
            lookat{node.child("lookat")},
            up{node.child("up")},
            horizontal_fov{node.child("horizontal_fov")},
            resolution{node.child("resolution")},
            max_bounces{node.child("max_bounces")},

            tan_fov_x{tan(horizontal_fov.radians())},
            tan_fov_y{tan(horizontal_fov.radians() * resolution.aspectRatio())},
            lookAt{Mat4::lookAt(position, lookat, up)} {}

    [[nodiscard]] Ray getRayToPixel(const uint64_t u, const uint64_t v) const {
        const float x_n = (static_cast<float>(u) + 0.5f) * resolution.reciprocalHorizontal;
        const float y_n = (static_cast<float>(v) + 0.5f) * resolution.reciprocalVertical;

        // plane z = 0, point coordinates
        const Vec3 plane =
                (lookAt * Vec4{Vec3{2 * x_n - 1, 2 * y_n - 1, -1} * Vec3{tan_fov_x, tan_fov_y, 1}}).toVec3();

        return Ray{position, (plane - position).normalized()};
    }
};

#endif
