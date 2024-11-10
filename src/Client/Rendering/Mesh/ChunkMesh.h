#pragma once

#include "pch.h"
#include "MeshData.h"

class ChunkMesh{
public:
    ChunkMesh(){}
    ~ChunkMesh(){}

    void CleanUp();

    void Create(uint8_t* verticesAndColors, uint16_t* indices, size_t vertexCount, size_t indexCount);
    void Draw() const;
    void DrawPoints() const;

    GLuint GetVaoID() const noexcept{return m_VaoId;}
    GLuint GetVboID() const noexcept{return m_VboId;}
    GLuint GetEboID() const noexcept{return m_EboId;}

    size_t GetVertexCount() const noexcept{return m_VertexCount;}
    size_t GetIndexCount() const noexcept{return m_IndexCount;}
private:
    GLuint m_VaoId = 0;
    GLuint m_VboId = 0;
    GLuint m_EboId = 0;
    size_t m_VertexCount = 0;
    size_t m_IndexCount = 0;
    bool m_IsCreated = false;
};