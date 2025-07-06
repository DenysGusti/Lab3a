#ifndef LAB3B_MAT4_HPP
#define LAB3B_MAT4_HPP

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
                1, 0, 0, 0,   // row 0
                0, 1, 0, 0,   // row 1
                0, 0, 1, 0,   // row 2
                0, 0, 0, 1    // row 3
        };
        return m;
    }

    static Mat4 translate(const Vec3 &t) {
        Mat4 m = identity();
        m.data[3] = t.x();
        m.data[7] = t.y();
        m.data[11] = t.z();
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
        const float c = cos(angleRad);
        const float s = sin(angleRad);
        m.data[5] = c;
        m.data[6] = -s;
        m.data[9] = s;
        m.data[10] = c;
        return m;
    }

    static Mat4 rotateY(const float angleRad) {
        Mat4 m = identity();
        const float c = cos(angleRad);
        const float s = sin(angleRad);
        m.data[0] = c;
        m.data[2] = s;
        m.data[8] = -s;
        m.data[10] = c;
        return m;
    }

    static Mat4 rotateZ(const float angleRad) {
        Mat4 m = identity();
        const float c = cos(angleRad);
        const float s = sin(angleRad);
        m.data[0] = c;
        m.data[1] = -s;
        m.data[4] = s;
        m.data[5] = c;
        return m;
    }

    static Mat4 lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up) {
        const Vec3 z = (eye - center).normalized();
        const Vec3 x = up.cross(z).normalized();
        const Vec3 y = z.cross(x);

        Mat4 m = identity();
        m.data[0] = x.x();
        m.data[1] = y.x();
        m.data[2] = z.x();
        m.data[3] = eye.x();
        m.data[4] = x.y();
        m.data[5] = y.y();
        m.data[6] = z.y();
        m.data[7] = eye.y();
        m.data[8] = x.z();
        m.data[9] = y.z();
        m.data[10] = z.z();
        m.data[11] = eye.z();
        return m;
    }

    [[nodiscard]] Mat4 transposed() const {
        Mat4 m{};
        for (size_t row = 0; row < 4; ++row)
            for (size_t col = 0; col < 4; ++col)
                m.data[col + row * 4] = data[row + col * 4];
        return m;
    }

    [[nodiscard]] Vec4 operator*(const Vec4 &v) const {
        Vec4 result{};
        for (size_t row = 0; row < 4; ++row)
            result.data[row] =
                    data[row * 4 + 0] * v.x() +
                    data[row * 4 + 1] * v.y() +
                    data[row * 4 + 2] * v.z() +
                    data[row * 4 + 3] * v.w();
        return result;
    }

    [[nodiscard]] Mat4 operator*(const Mat4 &other) const {
        Mat4 result{};
        for (size_t row = 0; row < 4; ++row)
            for (size_t col = 0; col < 4; ++col)
                for (size_t k = 0; k < 4; ++k)
                    result.data[row * 4 + col] += data[row * 4 + k] * other.data[k * 4 + col];
        return result;
    }
};

#endif

