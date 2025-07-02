#ifndef LAB3A_VEC3_HPP
#define LAB3A_VEC3_HPP

#include <cmath>
#include <array>
#include <exception>

#include "../../libs/pugixml/src/pugixml.hpp"

using namespace std;

struct Vec3 {
    array<float, 3> data{};

    Vec3() = default;

    Vec3(const float a, const float b, const float c) : data{a, b, c} {}

    explicit Vec3(const pugi::xml_node &node) {
        if (node.attribute("x") && node.attribute("y") && node.attribute("z")) {
            data[0] = node.attribute("x").as_float();
            data[1] = node.attribute("y").as_float();
            data[2] = node.attribute("z").as_float();
        } else if (node.attribute("r") && node.attribute("g") && node.attribute("b")) {
            data[0] = node.attribute("r").as_float();
            data[1] = node.attribute("g").as_float();
            data[2] = node.attribute("b").as_float();
        } else {
            cerr << "Vec3 XML node must contain either (x, y, z) or (r, g, b)." << endl;
            throw invalid_argument{"Vec3 XML node must contain either (x, y, z) or (r, g, b)."};
        }
    }

    [[nodiscard]] float x() const {
        return data[0];
    }

    [[nodiscard]] float y() const {
        return data[1];
    }

    [[nodiscard]] float z() const {
        return data[2];
    }

    float &x() {
        return data[0];
    }

    float &y() {
        return data[1];
    }

    float &z() {
        return data[2];
    }

    [[nodiscard]] float r() const {
        return data[0];
    }

    [[nodiscard]] float g() const {
        return data[1];
    }

    [[nodiscard]] float b() const {
        return data[2];
    }

    float &r() {
        return data[0];
    }

    float &g() {
        return data[1];
    }

    float &b() {
        return data[2];
    }

    [[nodiscard]] bool zero() const {
        return x() == 0 && y() == 0 && z() == 0;
    }

    [[nodiscard]] bool inf() const {
        return isinf(x()) || isinf(y()) || isinf(z());
    }

    [[nodiscard]] array<uint8_t, 3> toBytes() const {
        return {
                static_cast<uint8_t>(clamp(r(), 0.f, 1.f) * 255.f),
                static_cast<uint8_t>(clamp(g(), 0.f, 1.f) * 255.f),
                static_cast<uint8_t>(clamp(b(), 0.f, 1.f) * 255.f)
        };
    }

    [[nodiscard]] Vec3 operator+(const Vec3 &other) const {
        return Vec3{x() + other.x(), y() + other.y(), z() + other.z()};
    }

    Vec3 &operator+=(const Vec3 &other) {
        x() += other.x();
        y() += other.y();
        z() += other.z();
        return *this;
    }

    [[nodiscard]] Vec3 operator-(const Vec3 &other) const {
        return Vec3{x() - other.x(), y() - other.y(), z() - other.z()};
    }

    Vec3 &operator-=(const Vec3 &other) {
        x() -= other.x();
        y() -= other.y();
        z() -= other.z();
        return *this;
    }

    [[nodiscard]] Vec3 operator*(const Vec3 &other) const {
        return Vec3{x() * other.x(), y() * other.y(), z() * other.z()};
    }

    Vec3 &operator*=(const Vec3 &other) {
        x() *= other.x();
        y() *= other.y();
        z() *= other.z();
        return *this;
    }

    [[nodiscard]] Vec3 operator*(const float scalar) const {
        return Vec3{x() * scalar, y() * scalar, z() * scalar};
    }

    Vec3 &operator*=(const float scalar) {
        x() *= scalar;
        y() *= scalar;
        z() *= scalar;
        return *this;
    }

    [[nodiscard]] Vec3 operator/(const float scalar) const {
        const float reciprocal = 1.f / scalar;
        return Vec3{x() * reciprocal, y() * reciprocal, z() * reciprocal};
    }

    Vec3 &operator/=(const float scalar) {
        const float reciprocal = 1.f / scalar;
        x() *= reciprocal;
        y() *= reciprocal;
        z() *= reciprocal;
        return *this;
    }

    [[nodiscard]] Vec3 operator-() const {
        return Vec3{-x(), -y(), -z()};
    }

    [[nodiscard]] float dot(const Vec3 &other) const {
        return x() * other.x() + y() * other.y() + z() * other.z();
    }

    [[nodiscard]] Vec3 cross(const Vec3 &other) const {
        return Vec3{
                y() * other.z() - z() * other.y(),
                z() * other.x() - x() * other.z(),
                x() * other.y() - y() * other.x()
        };
    }

    [[nodiscard]] float length() const {
        return inf() ? numeric_limits<float>::infinity() : hypot(x(), y(), z());
    }

    [[nodiscard]] float lengthSquared() const {
        return x() * x() + y() * y() + z() * z();
    }

    [[nodiscard]] Vec3 normalized() const {
        const float len = length();
        return len > 0 ? *this / len : Vec3{0, 0, 0};
    }

    [[nodiscard]] Vec3 reflect(const Vec3 &normal) const {
        return *this - normal * (2.f * this->dot(normal));
    }
};

[[nodiscard]] Vec3 operator*(const float scalar, const Vec3 &v) {
    return v * scalar;
}

#endif
