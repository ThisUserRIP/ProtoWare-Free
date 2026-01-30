#include "pch.h"
#include "math3d.h"
#include "globals.h"

vec2 matrix4x4::worldtoscreen(vec3 pos) const {
    float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

    float w = m03 * pos.x + m13 * pos.y + m23 * pos.z + m33;

    if (w < 0.001f)
        return vec2(0, 0);
    float invW = 1.0f / w;

    float x = m00 * pos.x + m10 * pos.y + m20 * pos.z + m30;
    float y = m01 * pos.x + m11 * pos.y + m21 * pos.z + m31;

    float screenX = (screen_width / 2.0f) * (1.f + x * invW);
    float screenY = (screen_height / 2.0f) * (1.f - y * invW);

    return vec2(screenX, screenY);
}

vec2 matrix4x4::worldtoscreen(const vec3& world_pos, const matrix4x4& view_matrix, const matrix4x4& proj_matrix)
{
    matrix4x4 vp_matrix = proj_matrix * view_matrix;

    float x = vp_matrix.m[0][0] * world_pos.x + vp_matrix.m[1][0] * world_pos.y + vp_matrix.m[2][0] * world_pos.z + vp_matrix.m[3][0];
    float y = vp_matrix.m[0][1] * world_pos.x + vp_matrix.m[1][1] * world_pos.y + vp_matrix.m[2][1] * world_pos.z + vp_matrix.m[3][1];
    float w = vp_matrix.m[0][3] * world_pos.x + vp_matrix.m[1][3] * world_pos.y + vp_matrix.m[2][3] * world_pos.z + vp_matrix.m[3][3];

    if (w < 0.1f) {
        return vec2(0, 0);
    }

    vec2 ndc;
    ndc.x = x / w;
    ndc.y = y / w;

    float screenX = (screen_width / 2.0f) * (1.0f + ndc.x);
    float screenY = (screen_height / 2.0f) * (1.0f - ndc.y);

    return vec2(screenX, screenY);
}

matrix4x4 matrix4x4::operator*(const matrix4x4& other) const {
    matrix4x4 result{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[0][j] * other.m[i][0] +
                m[1][j] * other.m[i][1] +
                m[2][j] * other.m[i][2] +
                m[3][j] * other.m[i][3];
        }
    }
    return result;
}