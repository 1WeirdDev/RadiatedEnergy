#include "pch.h"
#include "Chunk.h"

Chunk::Chunk(){
    m_VertexIndex = 0;
    m_Vertices.resize(0);
    m_Indices.resize(0);
}
Chunk::~Chunk(){}

void Chunk::CreateBlockData(){

}
void Chunk::CreateMeshData(){

}
void Chunk::CreateMesh(){
    for(uint8_t z = 0; z < s_ChunkWidth; z++){
        for(uint8_t x = 0; x < s_ChunkWidth; x++){
            m_Vertices.emplace_back(0);
            m_Vertices.emplace_back(0);
            m_Vertices.emplace_back(0);
            
            m_Vertices.emplace_back(0);
            m_Vertices.emplace_back(1);
            m_Vertices.emplace_back(0);
            
            m_Vertices.emplace_back(1);
            m_Vertices.emplace_back(0);
            m_Vertices.emplace_back(0);
            
            m_Vertices.emplace_back(1);
            m_Vertices.emplace_back(1);
            m_Vertices.emplace_back(0);

            m_Indices.emplace_back(m_VertexIndex + 0);
            m_Indices.emplace_back(m_VertexIndex + 1);
            m_Indices.emplace_back(m_VertexIndex + 2);
            m_Indices.emplace_back(m_VertexIndex + 2);
            m_Indices.emplace_back(m_VertexIndex + 1);
            m_Indices.emplace_back(m_VertexIndex + 3);
            m_VertexIndex+=4;
        }
    }
    
    m_Mesh.Create(3, VT_UINT8, FT_UINT16, m_Vertices.data(), m_Indices.data(), m_Vertices.size(), m_Indices.size());
}

void Chunk::Tick(){}

void Chunk::Draw(){
    m_Mesh.Draw();
}