#include "pch.h"

#include "ChunkMesh.h"
#include "Core/Logger.h"

void ChunkMesh::CleanUp() noexcept{
    if(!m_IsCreated)return;
    glDeleteBuffers(2, &m_VboId);
    glDeleteVertexArrays(1, &m_VaoId);
    m_VaoId = 0;
    m_VboId = 0;
    m_EboId = 0;
    m_IsCreated = false;
}
void ChunkMesh::Create(uint8_t* vertices, float* normals, uint16_t* indices, size_t vertexCount, size_t normalCount, size_t indexCount) noexcept{
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(3, &m_VboId);

    glBindVertexArray(m_VaoId);
    
    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uint8_t) * vertexCount, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_UNSIGNED_BYTE, false, sizeof(uint8_t) * 4, nullptr);
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(uint8_t) * 4, (void*)(sizeof(uint8_t) * 3));

    glBindBuffer(GL_ARRAY_BUFFER, m_NboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalCount, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(uint8_t) * 3, nullptr);

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexCount, indices, GL_STATIC_DRAW);
    m_VertexCount = vertexCount;
    m_IndexCount = indexCount;
    m_IsCreated = true;
}

void ChunkMesh::Draw()const noexcept{
    if(!m_IsCreated)return;
    glBindVertexArray(m_VaoId);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, nullptr);
}

void ChunkMesh::DrawPoints() const noexcept{
    glDrawArrays(GL_POINTS, 0, m_VertexCount);
}