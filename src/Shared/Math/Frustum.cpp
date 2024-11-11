#include "pch.h"
#include "Frustum.h"

Frustum::Frustum(){}
void Frustum::ExtractFrustumPlanes(const Mat4x4& viewProjectionMatrix) {
    /*
    // Left
    m_FrustumPlanes[0] = viewProjectionMatrix.GetRow(3) + viewProjectionMatrix.GetRow(0);
    // Right
    m_FrustumPlanes[1] = viewProjectionMatrix.GetRow(3) - viewProjectionMatrix.GetRow(0);
    // Bottom
    m_FrustumPlanes[2] = viewProjectionMatrix.GetRow(3) + viewProjectionMatrix.GetRow(1);
    // Top
    m_FrustumPlanes[3] = viewProjectionMatrix.GetRow(3) - viewProjectionMatrix.GetRow(1);
    // Near
    m_FrustumPlanes[4] = viewProjectionMatrix.GetRow(3) + viewProjectionMatrix.GetRow(2);
    // Far
    m_FrustumPlanes[5] = viewProjectionMatrix.GetRow(3) - viewProjectionMatrix.GetRow(2);

    // Normalize the planes
    for (unsigned char i = 0; i < 6; i++) {
        Vec4<float> plane = m_FrustumPlanes[i];
        Vec3<float> f(plane.x, plane.y, plane.z);
        m_FrustumPlanes[i] /= f.GetMagnitude();
    }
    */
}

//bool CameraFrustum::IsChunkInFrustum(const glm::vec3& min, const glm::vec3& max)  {
bool Frustum::IsChunkInFrustum(short global_x, short global_z)  {
    /*glm::vec3 min(global_x * CHUNK_WIDTH, 0, global_z * CHUNK_WIDTH);
    glm::vec3 max(min.x + CHUNK_WIDTH, CHUNK_HEIGHT, min.z + CHUNK_WIDTH);
    for (unsigned char i = 0; i < 6; i++) {
        glm::vec3 positive_vertex = min;
        if (m_FrustumPlanes[i].x >= 0) positive_vertex.x = max.x;
        if (m_FrustumPlanes[i].y >= 0) positive_vertex.y = max.y;
        if (m_FrustumPlanes[i].z >= 0) positive_vertex.z = max.z;

        if (glm::dot(glm::vec3(m_FrustumPlanes[i]), positive_vertex) + m_FrustumPlanes[i].w < 0) {
            return false;
        }
    }*/
    return true;
}


bool Frustum::IsGroupChunkInFrustum(short group_x, short group_z, short group_size) {
    /*glm::vec3 min(group_x * CHUNK_WIDTH, 0, group_z * CHUNK_WIDTH);
    glm::vec3 max(min.x + CHUNK_WIDTH * group_size, CHUNK_HEIGHT, min.z + CHUNK_WIDTH * group_size);
    for (unsigned char i = 0; i < 6; i++) {
        glm::vec3 positive_vertex = min;
        if (m_FrustumPlanes[i].x >= 0) positive_vertex.x = max.x;
        if (m_FrustumPlanes[i].y >= 0) positive_vertex.y = max.y;
        if (m_FrustumPlanes[i].z >= 0) positive_vertex.z = max.z;

        if (glm::dot(glm::vec3(m_FrustumPlanes[i]), positive_vertex) + m_FrustumPlanes[i].w < 0) {
            return false;
        }
    }*/
    return true;
}