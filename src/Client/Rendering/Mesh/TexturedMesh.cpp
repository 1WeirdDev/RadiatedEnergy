#include "pch.h"

#include "Core/Logger.h"
#include "TexturedMesh.h"

void TexturedMesh::CleanUp(){
    if(!m_IsCreated)return;
    //Automatically deletes ebo with vbo tbo and ebo
    glDeleteBuffers(3, &m_VboId);
    glDeleteVertexArrays(1, &m_VaoId);
    m_VaoId = 0;
    m_VboId = 0;
    m_EboId = 0;
    m_IsCreated = false;
}

void TexturedMesh::BindVao() const{
    glBindVertexArray(m_VaoId);
}
void TexturedMesh::Create(unsigned char dimensions, VertexType vertexType, IndexType indexType, VertexType textureCoordType, void* vertices, void* indices, void* textureCoords, size_t vertexCount, size_t indexCount, size_t textureCoordCount){
    CORE_DEBUG("CREATING TEXTUREDD  MESH \n");
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(3, &m_VboId);

    GLuint glVertexType = vertexType + 0x1400;    //GL HAS OFFSET 0x1400
    GLuint dataSize = 0;

    //Vertices
    switch(vertexType){
    case VT_INT8:
        dataSize = sizeof(int8_t);
        break;
    case VT_UINT8:
        dataSize = sizeof(uint8_t);
        break;
    case VT_INT16:
        dataSize = sizeof(int16_t);
        break;
    case VT_UINT16:
        dataSize = sizeof(uint16_t);
        break;
    case VT_INT32:
        dataSize = sizeof(int32_t);
        break;
    case VT_UINT32:
        dataSize = sizeof(uint32_t);
        break;
    case VT_FLOAT:
        dataSize = sizeof(float);
        break;
    }
    
    glBindVertexArray(m_VaoId);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize * vertexCount, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dimensions, glVertexType, false, 0, nullptr);

    switch(indexType){ 
    case FT_UINT8:
        dataSize = sizeof(uint8_t);
        m_GLIndexType = GL_UNSIGNED_BYTE;
        break;
    case FT_UINT16:
        dataSize = sizeof(uint16_t);
        m_GLIndexType = GL_UNSIGNED_SHORT;
        break;
    case FT_UINT32:
        dataSize = sizeof(uint32_t);
        m_GLIndexType = GL_UNSIGNED_INT;
        break;
    default:
        CORE_WARN("Invalid Index Type for Basic mesh");
        break;
    }
    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize * indexCount, indices, GL_STATIC_DRAW);

    //Texture Coords
    
    //Vertices
    glVertexType = textureCoordType + 0x1400;    //GL HAS OFFSET 0x1400
    switch(textureCoordType){
    case VT_INT8:
        dataSize = sizeof(int8_t);
        break;
    case VT_UINT8:
        dataSize = sizeof(uint8_t);
        break;
    case VT_INT16:
        dataSize = sizeof(int16_t);
        break;
    case VT_UINT16:
        dataSize = sizeof(uint16_t);
        break;
    case VT_INT32:
        dataSize = sizeof(int32_t);
        break;
    case VT_UINT32:
        dataSize = sizeof(uint32_t);
        break;
    case VT_FLOAT:
        dataSize = sizeof(float);
        break;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, m_TboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize * textureCoordCount, textureCoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, glVertexType, false, 0, nullptr);

    m_VertexCount = vertexCount;
    m_IndexCount = indexCount;
    m_IsCreated = true;
    CORE_DEBUG("CREATED TEXTUREDD  MESH \n");
}
void TexturedMesh::Draw() const{
    if(!m_IsCreated)return;

    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glDrawElements(GL_TRIANGLES, m_IndexCount, m_GLIndexType, nullptr);
}

void TexturedMesh::DrawInstanced(size_t count) const{
    if(!m_IsCreated)return;
    
    glBindVertexArray(m_VaoId);
    glDrawElementsInstanced(GL_TRIANGLES, m_IndexCount, m_GLIndexType, nullptr, count);
}
void TexturedMesh::DrawInstancedNoBinding(size_t count) const{
    glDrawElementsInstanced(GL_TRIANGLES, m_IndexCount, m_GLIndexType, nullptr, count);
}