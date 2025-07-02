#ifndef LAB3A_VEC4_HPP
#define LAB3A_VEC4_HPP

#include <array>
#include <cmath>

#include "Vec3.hpp"

using namespace std;

struct Vec4 {
    array<float, 4> data{};

    Vec4() = default;

    Vec4(const float x, const float y, const float z, const float w) : data{x, y, z, w} {}

    explicit Vec4(const Vec3 &vec3, const float w = 1.f) : data{vec3.x(), vec3.y(), vec3.z(), w} {}

    [[nodiscard]] inline Vec3 toVec3() const {
        return Vec3{x(), y(), z()};
    }

    [[nodiscard]] inline float x() const {
        return data[0];
    }

    [[nodiscard]] inline float y() const {
        return data[1];
    }

    [[nodiscard]] inline float z() const {
        return data[2];
    }

    [[nodiscard]] inline float w() const {
        return data[3];
    }

    inline float &x() {
        return data[0];
    }

    inline float &y() {
        return data[1];
    }

    inline float &z() {
        return data[2];
    }

    inline float &w() {
        return data[3];
    }

    [[nodiscard]] inline float r() const {
        return data[0];
    }

    [[nodiscard]] inline float g() const {
        return data[1];
    }

    [[nodiscard]] inline float b() const {
        return data[2];
    }

    [[nodiscard]] inline float a() const {
        return data[3];
    }

    inline float &r() {
        return data[0];
    }

    inline float &g() {
        return data[1];
    }

    inline float &b() {
        return data[2];
    }

    inline float &a() {
        return data[3];
    }

    [[nodiscard]] inline Vec4 operator+(const Vec4 &other) const {
        return Vec4{x() + other.x(), y() + other.y(), z() + other.z(), w() + other.w()};
    }

    inline Vec4 &operator+=(const Vec4 &other) {
        x() += other.x();
        y() += other.y();
        z() += other.z();
        w() += other.w();
        return *this;
    }

    [[nodiscard]] inline Vec4 operator-(const Vec4 &other) const {
        return Vec4{x() - other.x(), y() - other.y(), z() - other.z(), w() - other.w()};
    }

    inline Vec4 &operator-=(const Vec4 &other) {
        x() -= other.x();
        y() -= other.y();
        z() -= other.z();
        w() -= other.w();
        return *this;
    }

    [[nodiscard]] inline Vec4 operator*(const float scalar) const {
        return Vec4{x() * scalar, y() * scalar, z() * scalar, w() * scalar};
    }

    inline Vec4 &operator*=(const float scalar) {
        x() *= scalar;
        y() *= scalar;
        z() *= scalar;
        w() *= scalar;
        return *this;
    }

    [[nodiscard]] inline Vec4 operator*(const Vec4 &other) const {
        return Vec4{x() * other.x(), y() * other.y(), z() * other.z(), w() * other.w()};
    }

    inline Vec4 &operator*=(const Vec4 &other) {
        x() *= other.x();
        y() *= other.y();
        z() *= other.z();
        w() *= other.w();
        return *this;
    }

    [[nodiscard]] inline Vec4 operator/(const float scalar) const {
        const float inv = 1.f / scalar;
        return Vec4{x() * inv, y() * inv, z() * inv, w() * inv};
    }

    inline Vec4 &operator/=(const float scalar) {
        const float inv = 1.f / scalar;
        x() *= inv;
        y() *= inv;
        z() *= inv;
        w() *= inv;
        return *this;
    }

    [[nodiscard]] inline Vec4 operator-() const {
        return Vec4{-x(), -y(), -z(), -w()};
    }

    [[nodiscard]] inline float dot(const Vec4 &other) const {
        return x() * other.x() + y() * other.y() + z() * other.z() + w() * other.w();
    }

    [[nodiscard]] inline float length() const {
        return sqrt(dot(*this));
    }

    [[nodiscard]] inline float lengthSquared() const {
        return dot(*this);
    }

    [[nodiscard]] inline Vec4 normalized() const {
        const float len = length();
        return len > 0 ? *this / len : Vec4{0, 0, 0, 0};
    }
};

[[nodiscard]] inline Vec4 operator*(const float scalar, const Vec4 &v) {
    return v * scalar;
}

#endif
