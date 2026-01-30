#include "pch.h"
#include "math3d.h"

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float scalar) : x(scalar), y(scalar) {}
vec2::vec2(float x, float y) : x(x), y(y) {}

float vec2::get_magnitude() const {
    return sqrtf(x * x + y * y);
}

float vec2::get_sqr_magnitude() const {
    return x * x + y * y;
}

void vec2::normalize() {
    float mag = get_magnitude();
    if (mag > 0.0f) {
        x /= mag;
        y /= mag;
    }
}

vec2 vec2::get_normalized() const {
    vec2 result = *this;
    result.normalize();
    return result;
}

float vec2::dot(const vec2& other) const {
    return x * other.x + y * other.y;
}

float vec2::get_distance(const vec2& other) const {
    return (*this - other).get_magnitude();
}

float vec2::get_sqr_distance(const vec2& other) const {
    return (*this - other).get_sqr_magnitude();
}

void vec2::to_string(char* buffer, size_t size) const {
    snprintf(buffer, size, "vec2(%.3f, %.3f)", x, y);
}


vec2 vec2::operator+(const vec2& other) const { return vec2(x + other.x, y + other.y); }
vec2 vec2::operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }
vec2 vec2::operator*(float scalar) const { return vec2(x * scalar, y * scalar); }
vec2 vec2::operator/(float scalar) const { return vec2(x / scalar, y / scalar); }

vec2& vec2::operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }
vec2& vec2::operator-=(const vec2& other) { x -= other.x; y -= other.y; return *this; }
vec2& vec2::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
vec2& vec2::operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

vec2 vec2::operator-() const { return vec2(-x, -y); }