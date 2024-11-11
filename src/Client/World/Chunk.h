#pragma once

#include "pch.h"

#include "Rendering/Mesh/BasicMesh.h"

class Chunk{
public:
    constexpr static uint8_t s_ChunkWidth = 16;
    constexpr static uint8_t s_ChunkHeight = 16;
    constexpr static uint16_t s_ChunkWidthSquared = s_ChunkWidth * s_ChunkWidth;
    constexpr static uint32_t s_ChunkSize = s_ChunkWidthSquared * s_ChunkHeight;
public:
    Chunk();
    ~Chunk();

    void CreateBlockData();
    void CreateMeshData();
    void CreateMesh();
private:
    uint8_t m_BlockData[s_ChunkSize];

private:
};