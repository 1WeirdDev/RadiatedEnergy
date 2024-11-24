#include "pch.h"
#include "Chunk.h"
#include "Core/Logger.h"

Chunk::Chunk(Vec2<int16_t> position):
    m_Position(position),
    m_GlobalPosition(position.m_X * s_ChunkWidth, position.m_Y * s_ChunkWidth),
    m_VertexIndex(0){
    m_Vertices.resize(0);
    m_Indices.resize(0);

    memset(m_PointData, 0, s_ChunkWidthSquared * s_ChunkHeight);

    for(uint8_t z = 0; z < s_ChunkWidth; z+=2){
        for(uint8_t x = 0; x < s_ChunkWidth; x+=2){
            SetPointId(x,2,z, 1);
        }
    }
}
Chunk::~Chunk(){}

bool Chunk::IsPointEnabled(uint8_t x, uint8_t y, uint8_t z) const noexcept{
    if(x < 0 || x >= s_ChunkWidth || y < 0 || y >= s_ChunkHeight || z < 0 || z >= s_ChunkWidth)return false;
    return m_PointData[y * s_ChunkWidthSquared + z * s_ChunkWidth + x] > 0;
}
void Chunk::SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept{
    if(x < 0 || x >= s_ChunkWidth || y < 0 || y >= s_ChunkHeight || z < 0 || z >= s_ChunkWidth)return;
    m_PointData[y * s_ChunkWidthSquared + z * s_ChunkWidth + x] = id;
}
void Chunk::CreateBlockData(){
}
void Chunk::CreateMeshData(){
    uint8_t blockId = 0;
    m_Vertices.resize(0);
    m_Indices.resize(0);
    m_VertexIndex = 0;

    for(uint8_t y = 0; y < s_ChunkHeight - 1; y++){
        for(uint8_t z = 0; z < s_ChunkWidth - 1; z++){
            blockId = (uint8_t)((uint8_t)(IsPointEnabled(0, y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (uint8_t)(IsPointEnabled(0, y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0));


            for(uint8_t x = 0; x < s_ChunkWidth - 1; x++){
                //We do *2 because 1 is half of a block and 2 is a full point
                //Then we scale it in the shader
                blockId <<= 4;
                blockId &= 0b11110000;
                blockId |=
                (IsPointEnabled(x + 1,y + 1, z + 0) ? (uint8_t)FaceBit::FrontTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 0) ? (uint8_t)FaceBit::FrontBottomRight : 0) |
                (IsPointEnabled(x + 1,y + 1, z + 1) ? (uint8_t)FaceBit::BackTopRight : 0) |
                (IsPointEnabled(x + 1,y + 0, z + 1) ? (uint8_t)FaceBit::BackBottomRight : 0);

                CreateBlock(x* 2, y * 2, z * 2, blockId);
            }
        }
    }

    m_Normals.reserve((m_Vertices.size() / 4) * 3);
    for(size_t i = 0; i < m_Vertices.size(); i+=12){
        Vec3<float> p0(m_Vertices[i], m_Vertices[i+1], m_Vertices[i+2]);
        Vec3<float> p1(m_Vertices[i+4], m_Vertices[i+5], m_Vertices[i+6]);
        Vec3<float> p2(m_Vertices[i+8], m_Vertices[i+9], m_Vertices[i+10]);

        Vec3<float> edge1 = p1 - p0;
        Vec3<float> edge2 = p2 - p0;
        Vec3<float> normal = edge1.Cross(edge2);
        normal.Normalize();

        m_Normals.emplace_back(normal.m_X);
        m_Normals.emplace_back(normal.m_Y);
        m_Normals.emplace_back(normal.m_Z);
        m_Normals.emplace_back(normal.m_X);
        m_Normals.emplace_back(normal.m_Y);
        m_Normals.emplace_back(normal.m_Z);
        m_Normals.emplace_back(normal.m_X);
        m_Normals.emplace_back(normal.m_Y);
        m_Normals.emplace_back(normal.m_Z);
    }
#ifndef DIST
    m_PointVertexIndex = 0;
    m_PointVertices.resize(0);
    m_PointIndices.resize(0);
    for(uint8_t y = 0; y < s_ChunkHeight; y++){
        for(uint8_t x = 0; x < s_ChunkWidth; x++){
            for(uint8_t z = 0; z < s_ChunkWidth; z++){
                m_PointVertices.reserve(m_PointVertices.size() + 24);
                m_PointIndices.reserve(m_PointIndices.size() + 6);

                m_PointVertices.emplace_back(x * s_PointDivisor);
                m_PointVertices.emplace_back(y * s_PointDivisor);
                m_PointVertices.emplace_back(z * s_PointDivisor);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x * s_PointDivisor);
                m_PointVertices.emplace_back(y * s_PointDivisor + 1);
                m_PointVertices.emplace_back(z * s_PointDivisor);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x * s_PointDivisor + 1);
                m_PointVertices.emplace_back(y * s_PointDivisor);
                m_PointVertices.emplace_back(z * s_PointDivisor);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x* s_PointDivisor+ 1);
                m_PointVertices.emplace_back(y* s_PointDivisor+ 1);
                m_PointVertices.emplace_back(z* s_PointDivisor);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x * s_PointDivisor);
                m_PointVertices.emplace_back(y * s_PointDivisor);
                m_PointVertices.emplace_back(z * s_PointDivisor + 1);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x * s_PointDivisor);
                m_PointVertices.emplace_back(y * s_PointDivisor + 1);
                m_PointVertices.emplace_back(z * s_PointDivisor + 1);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x * s_PointDivisor + 1);
                m_PointVertices.emplace_back(y * s_PointDivisor);
                m_PointVertices.emplace_back(z * s_PointDivisor + 1);
                m_PointVertices.emplace_back(0);

                m_PointVertices.emplace_back(x* s_PointDivisor+ 1);
                m_PointVertices.emplace_back(y* s_PointDivisor+ 1);
                m_PointVertices.emplace_back(z* s_PointDivisor + 1);
                m_PointVertices.emplace_back(0);

                m_PointIndices.push_back(m_PointVertexIndex);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 1);
                m_PointIndices.push_back(m_PointVertexIndex + 2);
                m_PointIndices.push_back(m_PointVertexIndex + 3);
                m_PointIndices.push_back(m_PointVertexIndex + 4);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 6);
                m_PointIndices.push_back(m_PointVertexIndex + 5);
                m_PointIndices.push_back(m_PointVertexIndex + 7);
                m_PointVertexIndex+=8;
            }
        }
    }
#endif
}
void Chunk::CreateMesh(){
    m_Mesh.Create(m_Vertices.data(), m_Normals.data(), m_Indices.data(), m_Vertices.size(), m_Normals.size(), m_Indices.size());
#ifndef DIST
    m_PointMesh.Create(m_PointVertices.data(), m_PointIndices.data(), m_PointVertices.size(), m_PointIndices.size());
#endif
}

void Chunk::Tick(){}

void Chunk::Draw() const noexcept{
    m_Mesh.Draw();
}
#ifndef DIST
void Chunk::DrawPoints() const noexcept{
    m_PointMesh.Draw();
}
#endif