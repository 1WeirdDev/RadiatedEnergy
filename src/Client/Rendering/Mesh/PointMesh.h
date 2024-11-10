#pragma once

#include "pch.h"
#include "Core/Logger.h"
#include "MeshData.h"

class PointMesh{
public:
    PointMesh(){}
    ~PointMesh(){}

    void CleanUp();

    void Create(uint8_t* vertices, uint16_t* indices, size_t vertexCount, size_t indexCount);
    void Draw() const;
private:
    GLuint m_VaoId = 0;
    GLuint m_VboId = 0;
    GLuint m_EboId = 0;
    size_t m_IndexCount = 0;
    bool m_IsCreated = false;
};