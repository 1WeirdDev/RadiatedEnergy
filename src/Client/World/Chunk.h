#pragma once

#include "pch.h"

#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Rendering/Mesh/ChunkMesh.h"
#include "Rendering/Mesh/PointMesh.h"

enum class FaceBit{
    FrontTopLeft =      (uint8_t)(1 << 7),
    FrontBottomLeft =   (uint8_t)(1 << 6),
    BackTopLeft =       (uint8_t)(1 << 5),
    BackBottomLeft =    (uint8_t)(1 << 4),
    FrontTopRight =     (uint8_t)(1 << 3),
    FrontBottomRight =  (uint8_t)(1 << 2),
    BackTopRight =      (uint8_t)(1 << 1),
    BackBottomRight =   (uint8_t)(1 << 0)
};

class Chunk{
public:
    constexpr static uint8_t s_ChunkWidth =  16;
    constexpr static uint8_t s_ChunkHeight = 16;
    constexpr static uint16_t s_ChunkWidthSquared = s_ChunkWidth * s_ChunkWidth;
    constexpr static uint32_t s_ChunkSize = s_ChunkWidthSquared * s_ChunkHeight;
    //The point cube will be x times smaller than scale 
    constexpr static uint8_t s_PointDivisor = 4;
public:
    //Maybe make infinite with int32_t or just add some sort of world border
    Chunk(Vec2<int16_t> position);
    ~Chunk();

    void Tick();
    void Draw() const noexcept;
#ifndef DIST
    void DrawPoints() const noexcept;
#endif

    void CreateBlockData();
    void CreateMeshData();
    void CreateMesh();

    /// @brief Checks if a point is enablssssed at a position
    /// @return returns if a point is greater than 0 or returns 0 if out of chunk range
    bool IsPointEnabled(uint8_t x, uint8_t y, uint8_t z) const noexcept;
    void SetPointId(uint8_t x, uint8_t y, uint8_t z, uint8_t id) noexcept;
public:
    const Vec2<int16_t>& GetPosition() const noexcept{return m_Position;}
    const Vec2<int32_t>& GetGlobalPosition() const noexcept{return m_GlobalPosition;}
private:
    //Block coordinates must be their real world coordinates * 2. This then gets divided by 2 in the vertex shader so they are within range
    void CreateBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);
    void CreateSingle(uint8_t x, uint8_t y, uint8_t z, uint8_t blockId);

    void AddVertex(uint8_t x, uint8_t y, uint8_t z, uint8_t c);
    void AddFaces(uint8_t faces);
    uint8_t m_PointData[s_ChunkSize];
private:
    Vec2<int16_t> m_Position;
    Vec2<int32_t> m_GlobalPosition;
private:
    std::vector<uint8_t> m_Vertices;
    std::vector<float> m_Normals;
    std::vector<uint16_t> m_Indices;
    uint16_t m_VertexIndex = 0;
    ChunkMesh m_Mesh;
private:
#ifndef DIST
    std::vector<uint8_t> m_PointVertices;
    std::vector<uint16_t> m_PointIndices;
    uint16_t m_PointVertexIndex = 0;
    PointMesh m_PointMesh;
#endif
};