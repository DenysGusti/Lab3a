#ifndef LAB3A_MAT4_HPP
#define LAB3A_MAT4_HPP

#include <array>
#include <cmath>

#include "Vec3.hpp"
#include "Vec4.hpp"

using namespace std;

struct Mat4 {
    array<float, 16> data{};

    Mat4() = default;

    static Mat4 identity() {
        Mat4 m{};
        m.data = {
                1, 0, 0, 0,   // Column 0
                0, 1, 0, 0,   // Column 1
                0, 0, 1, 0,   // Column 2
                0, 0, 0, 1    // Column 3
        };
        return m;
    }

    static Mat4 translate(const Vec3 &t) {
        Mat4 m = identity();
        m.data[12] = t.x();
        m.data[13] = t.y();
        m.data[14] = t.z();
        return m;
    }

    static Mat4 scale(const Vec3 &s) {
        Mat4 m = identity();
        m.data[0] = s.x();
        m.data[5] = s.y();
        m.data[10] = s.z();
        return m;
    }

    static Mat4 rotateX(const float angleRad) {
        Mat4 m = identity();
        float c = cos(angleRad), s = sin(angleRad);
        m.data[5] = c;
        m.data[6] = s;
        m.data[9] = -s;
        m.data[10] = c;
        return m;
    }

    static Mat4 rotateY(const float angleRad) {
        Mat4 m = identity();
        float c = cos(angleRad), s = sin(angleRad);
        m.data[0] = c;
        m.data[2] = -s;
        m.data[8] = s;
        m.data[10] = c;
        return m;
    }

    static Mat4 rotateZ(const float angleRad) {
        Mat4 m = identity();
        float c = cos(angleRad), s = sin(angleRad);
        m.data[0] = c;
        m.data[1] = s;
        m.data[4] = -s;
        m.data[5] = c;
        return m;
    }

    static Mat4 lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up) {
        Vec3 f = (eye - center).normalized();
        Vec3 r = up.cross(f).normalized();
        Vec3 u = f.cross(r);

        Mat4 m = identity();
        m.data[0] = r.x();
        m.data[4] = r.y();
        m.data[8] = r.z();
        m.data[1] = u.x();
        m.data[5] = u.y();
        m.data[9] = u.z();
        m.data[2] = f.x();
        m.data[6] = f.y();
        m.data[10] = f.z();
        m.data[12] = eye.x();
        m.data[13] = eye.y();
        m.data[14] = eye.z();
        return m;
    }

    [[nodiscard]] Mat4 transposed() const {
        Mat4 m{};
        for (size_t row = 0; row < 4; ++row)
            for (size_t col = 0; col < 4; ++col)
                m.data[row + col * 4] = data[col + row * 4];
        return m;
    }

    [[nodiscard]] Vec4 operator*(const Vec4 &v) const {
        Vec4 result{};
        for (size_t i = 0; i < 4; ++i) {
            result.data[i] =
                    data[0 + i] * v.x() +
                    data[4 + i] * v.y() +
                    data[8 + i] * v.z() +
                    data[12 + i] * v.w();
        }
        return result;
    }

    [[nodiscard]] Mat4 operator*(const Mat4 &other) const {
        Mat4 result{};
        for (size_t row = 0; row < 4; ++row)
            for (size_t col = 0; col < 4; ++col)
                for (size_t k = 0; k < 4; ++k)
                    result.data[col * 4 + row] += data[k * 4 + row] * other.data[col * 4 + k];
        return result;
    }
};

#endif

