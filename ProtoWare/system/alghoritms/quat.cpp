#include "pch.h"
#include "math3d.h"

constexpr float radToDeg = 180.0f / static_cast<float>(PI);

quat::quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
quat::quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

quat::quat(const vec3& axis, float angle_rad) {
    float half_angle = angle_rad * 0.5f;
    float s = sinf(half_angle);
    vec3 normalized_axis = axis.get_normalized();
    x = normalized_axis.x * s;
    y = normalized_axis.y * s;
    z = normalized_axis.z * s;
    w = cosf(half_angle);
}

quat::quat(const vec3& v) : x(v.x), y(v.y), z(v.z), w(0.0f) {}

quat quat::look_rotation(const vec3& forward, const vec3& up) {
    vec3 f = forward.get_normalized();
    vec3 u = up.get_normalized();
    vec3 r = u.cross(f).get_normalized();
    u = f.cross(r);

    float m00 = r.x, m01 = u.x, m02 = f.x;
    float m10 = r.y, m11 = u.y, m12 = f.y;
    float m20 = r.z, m21 = u.z, m22 = f.z;

    float trace = m00 + m11 + m22;
    quat q;

    if (trace > 0.0f)
    {
        float s = sqrtf(trace + 1.0f) * 2.0f;
        q.w = 0.25f * s;
        q.x = (m21 - m12) / s;
        q.y = (m02 - m20) / s;
        q.z = (m10 - m01) / s;
    }
    else if ((m00 > m11) && (m00 > m22))
    {
        float s = sqrtf(1.0f + m00 - m11 - m22) * 2.0f;
        q.w = (m21 - m12) / s;
        q.x = 0.25f * s;
        q.y = (m01 + m10) / s;
        q.z = (m02 + m20) / s;
    }
    else if (m11 > m22)
    {
        float s = sqrtf(1.0f + m11 - m00 - m22) * 2.0f;
        q.w = (m02 - m20) / s;
        q.x = (m01 + m10) / s;
        q.y = 0.25f * s;
        q.z = (m12 + m21) / s;
    }
    else
    {
        float s = sqrtf(1.0f + m22 - m00 - m11) * 2.0f;
        q.w = (m10 - m01) / s;
        q.x = (m02 + m20) / s;
        q.y = (m12 + m21) / s;
        q.z = 0.25f * s;
    }

    return q;
}
quat quat::from_euler_angles(float pitch_deg, float yaw_deg, float roll_deg) {
    float pitch_rad = pitch_deg * DEG_TO_RAD;
    float yaw_rad = yaw_deg * DEG_TO_RAD;
    float roll_rad = roll_deg * DEG_TO_RAD;

    float half_pitch = pitch_rad * 0.5f;
    float half_yaw = yaw_rad * 0.5f;
    float half_roll = roll_rad * 0.5f;

    float cos_p = cos(half_pitch);
    float sin_p = sin(half_pitch);
    float cos_y = cos(half_yaw);
    float sin_y = sin(half_yaw);
    float cos_r = cos(half_roll);
    float sin_r = sin(half_roll);

    quat result;
    result.w = cos_y * cos_p * cos_r + sin_y * sin_p * sin_r;
    result.x = cos_y * sin_p * cos_r - sin_y * cos_p * sin_r;
    result.y = sin_y * cos_p * cos_r + cos_y * sin_p * sin_r;
    result.z = cos_y * cos_p * sin_r - sin_y * sin_p * cos_r;

    return result;
}
quat quat::from_euler_angles(const vec3& euler_angles_deg) {
    return from_euler_angles(euler_angles_deg.x, euler_angles_deg.y, euler_angles_deg.z);
}

float quat::get_magnitude() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

float quat::get_sqr_magnitude() const {
    return x * x + y * y + z * z + w * w;
}

void quat::normalize() {
    float mag = get_magnitude();
    if (mag > 0.0f) {
        x /= mag; y /= mag; z /= mag; w /= mag;
    }
}

quat quat::get_normalized() const {
    quat q = *this;
    q.normalize();
    return q;
}

quat quat::conjugate() const {
    return quat(-x, -y, -z, w);
}

quat quat::inverse() const {
    return conjugate() / get_sqr_magnitude();
}

vec3 quat::get_vector_part() const {
    return vec3(x, y, z);
}

float NormalizeAngle(float angle) {
    angle = fmodf(angle + 180.0f, 360.0f);
    if (angle < 0.0f)
        angle += 360.0f;
    return angle - 180.0f;
}

vec3 NormalizeAngles(vec3 angles) {
    angles.x = NormalizeAngle(angles.x);
    angles.y = NormalizeAngle(angles.y);
    angles.z = NormalizeAngle(angles.z);
    return angles;
}

vec3 quat::to_euler_angles() const {
    float sqw = w * w;
    float sqx = x * x;
    float sqy = y * y;
    float sqz = z * z;
    float unit = sqx + sqy + sqz + sqw;
    float test = x * w - y * z;

    vec3 v;

    if (test > 0.4995f * unit) {
        v.y = 2.0f * std::atan2(y, x);
        v.x = static_cast<float>(PI) / 2.0f;
        v.z = 0.0f;
        return NormalizeAngles(v * radToDeg);
    }

    if (test < -0.4995f * unit) {
        v.y = -2.0f * std::atan2(y, x);
        v.x = -static_cast<float>(PI) / 2.0f;
        v.z = 0.0f;
        return NormalizeAngles(v * radToDeg);
    }

    // Swizzled quaternion
    //Vector4 q(w, z, x, y);
    quat q;
    q.x = w;
    q.y = z;
    q.z = x;
    q.w = y;

    v.y = std::atan2(2.0f * q.x * q.w + 2.0f * q.y * q.z, 1.0f - 2.0f * (q.z * q.z + q.w * q.w)); // Yaw
    v.x = std::asin(2.0f * (q.x * q.z - q.w * q.y));                                              // Pitch
    v.z = std::atan2(2.0f * q.x * q.y + 2.0f * q.z * q.w, 1.0f - 2.0f * (q.y * q.y + q.z * q.z)); // Roll

    return NormalizeAngles(v * radToDeg);
}

vec3 quat::get_forward() const {
    return (*this) * vec3(0.0f, 0.0f, 1.0f);
}

vec3 quat::get_up() const {
    return (*this) * vec3(0.0f, 1.0f, 0.0f);
}

void quat::to_string(char* buffer, size_t size) const {
    snprintf(buffer, size, "quat(%.3f, %.3f, %.3f, %.3f)", x, y, z, w);
}

quat quat::operator+(const quat& other) const { return quat(x + other.x, y + other.y, z + other.z, w + other.w); }
quat quat::operator-(const quat& other) const { return quat(x - other.x, y - other.y, z - other.z, w - other.w); }
quat quat::operator*(float scalar) const { return quat(x * scalar, y * scalar, z * scalar, w * scalar); }
quat quat::operator/(float scalar) const { return quat(x / scalar, y / scalar, z / scalar, w / scalar); }

quat quat::operator*(const quat& other) const {
    return quat(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}