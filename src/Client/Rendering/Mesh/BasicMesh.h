#pragma once

#include "pch.h"
#include "MeshData.h"

class BasicMesh{
public:
    BasicMesh(){}
    ~BasicMesh(){}

    void CleanUp();

    void Create(unsigned char dimensions, VertexType vertexType, IndexType indexType, void* vertices, void* indices, size_t vertexCount, size_t indexCount);
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
    GLuint m_GLIndexType = 0;
    size_t m_VertexCount = 0;
    size_t m_IndexCount = 0;
    bool m_IsCreated = false;
};