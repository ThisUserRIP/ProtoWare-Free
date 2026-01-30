#include "pch.h"
#include "math3d.h"
#include <algorithm>

vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
vec3::vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}
vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

float vec3::get_magnitude() const {
    return sqrtf(x * x + y * y + z * z);
}

float vec3::get_sqr_magnitude() const {
    return x * x + y * y + z * z;
}

void vec3::normalize() {
    float mag = get_magnitude();
    if (mag > 0.0f) {
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

vec3 vec3::get_forward() const {
    float pitch = x * DEG_TO_RAD;
    float yaw = y * DEG_TO_RAD;

    vec3 forward;
    forward.x = -cosf(pitch) * sinf(yaw);
    forward.y = -sinf(pitch);
    forward.z = cosf(pitch) * cosf(yaw);
    return forward;
}

vec3 vec3::get_normalized() const {
    vec3 result = *this;
    result.normalize();
    return result;
}

vec3 vec3::to_euler() const {
    return vec3(
        -asinf(y) * RAD_TO_DEG,
        atan2f(x, z) * RAD_TO_DEG,
        0
    );
}

float vec3::dot(const vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

vec3 vec3::cross(const vec3& other) const {
    return vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float vec3::get_distance(const vec3& other) const {
    return (*this - other).get_magnitude();
}
float vec3::distance(const vec3& a, const vec3& b) {
    return (a - b).get_magnitude();
}

float vec3::get_sqr_distance(const vec3& other) const {
    return (*this - other).get_sqr_magnitude();
}

void vec3::to_string(char* buffer, size_t size) const {
    snprintf(buffer, size, "vec3(%.3f, %.3f, %.3f)", x, y, z);
}

float vec3::compute_w(vec3 v, matrix4x4 viewMatrix) {
    float w =
        viewMatrix.m[0][3] * v.x +
        viewMatrix.m[1][3] * v.y +
        viewMatrix.m[2][3] * v.z +
        viewMatrix.m[3][3];
    return w;
}
vec3 vec3::clip_behind_camera(vec3 from, vec3 to, vec3 cam_pos, vec3 cam_forward, float near_dist) {
    vec3 dir = to - from;
    float dotFrom = (from - cam_pos).dot(cam_forward);
    float dotTo = (to - cam_pos).dot(cam_forward);

    float t = (near_dist - dotFrom) / (dotTo - dotFrom);
    t = std::clamp(t, 0.0f, 1.0f);
    return from + (dir * t);
}

vec3 vec3::operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
vec3 vec3::operator-(const vec3& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
vec3 vec3::operator*(float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
vec3 vec3::operator/(float scalar) const { return vec3(x / scalar, y / scalar, z / scalar); }

vec3& vec3::operator+=(const vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
vec3& vec3::operator-=(const vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
vec3& vec3::operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
vec3& vec3::operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }
vec3& vec3::operator*=(const vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
vec3& vec3::operator/=(const vec3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

vec3 vec3::operator-() const { return vec3(-x, -y, -z); }
bool vec3::operator==(const vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
}
bool vec3::operator!=(const vec3& other) const {
    return x != other.x || y != other.y || z != other.z;
}