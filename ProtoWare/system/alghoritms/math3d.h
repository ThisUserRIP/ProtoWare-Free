#pragma once
#include "pch.h"
#include <cmath>

constexpr float PI = 3.1415926535f;
constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;

class vec2;
class vec3;
class quat;
class matrix4x4;

class vec2 {
public:
    float x, y;

    vec2();
    vec2(float scalar);
    vec2(float x, float y);

    float get_magnitude() const;
    float get_sqr_magnitude() const;
    void normalize();
    vec2 get_normalized() const;
    float dot(const vec2& other) const;
    float get_distance(const vec2& other) const;
    float get_sqr_distance(const vec2& other) const;
    void to_string(char* buffer, size_t size) const;

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(float scalar) const;
    vec2 operator/(float scalar) const;
    vec2& operator+=(const vec2& other);
    vec2& operator-=(const vec2& other);
    vec2& operator*=(float scalar);
    vec2& operator/=(float scalar);
    vec2 operator-() const;
};

class vec3 {
public:
    float x, y, z;

    vec3();
    vec3(float scalar);
    vec3(float x, float y, float z);

    float get_magnitude() const;
    float get_sqr_magnitude() const;
    void normalize();
    vec3 get_forward() const;
    vec3 get_normalized() const;
    vec3 to_euler() const;
    float dot(const vec3& other) const;
    vec3 cross(const vec3& other) const;
    float get_distance(const vec3& other) const;
    static float distance(const vec3& a, const vec3& b);
    float get_sqr_distance(const vec3& other) const;
    void to_string(char* buffer, size_t size) const;
    static float compute_w(vec3 v, matrix4x4 viewMatrix);
    static vec3 clip_behind_camera(vec3 from, vec3 to, vec3 cam_pos, vec3 cam_forward, float near_dist = 0.01f);

    vec3 operator+(const vec3& other) const;
    vec3 operator-(const vec3& other) const;
    vec3 operator*(float scalar) const;
    vec3 operator/(float scalar) const;
    vec3& operator+=(const vec3& other);
    vec3& operator-=(const vec3& other);
    vec3& operator*=(float scalar);
    vec3& operator/=(float scalar);
    vec3& operator*=(const vec3& other);
    vec3& operator/=(const vec3& other);
    vec3 operator-() const;
    bool operator==(const vec3& other) const;
    bool operator!=(const vec3& other) const;
};

class vec3i {
public:
    int x, y, z;

    vec3i();
    vec3i(int scalar);
    vec3i(int x, int y, int z);

    int get_aaab_distance() const;
    void to_string(char* buffer, size_t size) const;

    vec3i operator+(const vec3i& other) const;
    vec3i operator-(const vec3i& other) const;
    vec3i operator*(int scalar) const;
    vec3i operator/(int scalar) const;
    vec3i& operator+=(const vec3i& other);
    vec3i& operator-=(const vec3i& other);
    vec3i& operator*=(int scalar);
    vec3i& operator/=(int scalar);
    vec3i& operator*=(const vec3i& other);
    vec3i& operator/=(const vec3i& other);
    vec3i operator-() const;
    bool operator==(const vec3i& other) const;
};

class vec4i {
public:
    int x, y, z, w;
};

class quat {
public:
    float x, y, z, w;

    quat();
    quat(float x, float y, float z, float w);
    quat(const vec3& axis, float angle_rad);
    quat(const vec3& v);

    static quat look_rotation(const vec3& forward, const vec3& up);
    static quat from_euler_angles(float pitch_deg, float yaw_deg, float roll_deg);
    static quat from_euler_angles(const vec3& euler_angles_deg);
    float get_magnitude() const;
    float get_sqr_magnitude() const;
    void normalize();
    quat get_normalized() const;
    quat conjugate() const;
    quat inverse() const;
    vec3 get_vector_part() const;
    vec3 to_euler_angles() const;
    void to_string(char* buffer, size_t size) const;

    vec3 get_forward() const;
    vec3 get_up() const;

    quat operator+(const quat& other) const;
    quat operator-(const quat& other) const;
    quat operator*(float scalar) const;
    quat operator/(float scalar) const;
    quat operator*(const quat& other) const;
};

class ray3d {
public:
    vec3 origin;
    vec3 direction;
};

class rayhit3d {
public:
    vec3 point;
    vec3 normal;
    uint32 face_id;
    float distance;
    vec2 uv;
    int collider;
};

inline vec2 operator*(float scalar, const vec2& v) {
    return v * scalar;
}

inline vec3 operator*(float scalar, const vec3& v) {
    return v * scalar;
}

inline quat operator*(float scalar, const quat& q) {
    return q * scalar;
}

inline vec3 operator*(const quat& q, const vec3& v) {
    /*quat p(v);
    quat q_inv = q.conjugate();
    quat rotated_p = q * p * q_inv;
    return rotated_p.get_vector_part();*/

    float _x = q.x * 2.0f;
    float _y = q.y * 2.0f;
    float _z = q.z * 2.0f;
    float xx = q.x * _x;
    float yy = q.y * _y;
    float zz = q.z * _z;
    float xy = q.x * _y;
    float xz = q.x * _z;
    float yz = q.y * _z;
    float wx = q.w * _x;
    float wy = q.w * _y;
    float wz = q.w * _z;

    vec3 result;
    result.x = (1.0f - (yy + zz)) * v.x + (xy - wz) * v.y + (xz + wy) * v.z;
    result.y = (xy + wz) * v.x + (1.0f - (xx + zz)) * v.y + (yz - wx) * v.z;
    result.z = (xz - wy) * v.x + (yz + wx) * v.y + (1.0f - (xx + yy)) * v.z;

    return result;
}

class matrix4x4 {
public:
    float m[4][4];

    vec2 worldtoscreen(vec3 pos) const;
    static vec2 worldtoscreen(const vec3& world_pos, const matrix4x4& view_matrix, const matrix4x4& proj_matrix);

    matrix4x4 operator*(const matrix4x4& other) const;
};