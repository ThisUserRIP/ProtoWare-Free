#include "pch.h"
#include "math3d.h"

vec3i::vec3i() : x(0.0f), y(0.0f), z(0.0f) {}
vec3i::vec3i(int scalar) : x(scalar), y(scalar), z(scalar) {}
vec3i::vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

void vec3i::to_string(char* buffer, size_t size) const {
    snprintf(buffer, size, "vec3i(%i, %i, %i)", x, y, z);
}

vec3i vec3i::operator+(const vec3i& other) const { return vec3i(x + other.x, y + other.y, z + other.z); }
vec3i vec3i::operator-(const vec3i& other) const { return vec3i(x - other.x, y - other.y, z - other.z); }
vec3i vec3i::operator*(int scalar) const { return vec3i(x * scalar, y * scalar, z * scalar); }
vec3i vec3i::operator/(int scalar) const { return vec3i(x / scalar, y / scalar, z / scalar); }

vec3i& vec3i::operator+=(const vec3i& other) { x += other.x; y += other.y; z += other.z; return *this; }
vec3i& vec3i::operator-=(const vec3i& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
vec3i& vec3i::operator*=(int scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
vec3i& vec3i::operator/=(int scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }
vec3i& vec3i::operator*=(const vec3i& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
vec3i& vec3i::operator/=(const vec3i& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

vec3i vec3i::operator-() const { return vec3i(-x, -y, -z); }

bool vec3i::operator==(const vec3i& other) const { return other.x == x && other.y == y && other.z == z; }