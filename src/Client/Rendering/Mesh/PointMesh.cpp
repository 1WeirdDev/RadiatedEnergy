#include "pch.h"

#include "PointMesh.h"
#include "Core/Logger.h"

void PointMesh::CleanUp(){
    if(!m_IsCreated)return;
    glDeleteBuffers(2, &m_VboId);
    glDeleteVertexArrays(1, &m_VaoId);
    m_VaoId = 0;
    m_VboId = 0;
    m_EboId = 0;
    m_IsCreated = false;
}
void PointMesh::Create(uint8_t* vertices, uint16_t* indices, size_t vertexCount, size_t indexCount){
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(1, &m_VboId);
    glGenBuffers(1, &m_EboId);

    glBindVertexArray(m_VaoId);

    //Vertices
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uint8_t) * vertexCount, vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_UNSIGNED_BYTE, false, sizeof(uint8_t) * 4, nullptr);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, sizeof(uint8_t) * 4, (void*)(sizeof(uint8_t) * 3));

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexCount, indices, GL_STATIC_DRAW);
    m_IndexCount = indexCount;
    m_IsCreated = true;
}

void PointMesh::Draw()const{
    if(!m_IsCreated)return;
    glBindVertexArray(m_VaoId);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, nullptr);
}