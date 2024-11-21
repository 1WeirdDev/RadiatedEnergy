#pragma once

#include "pch.h"
#include "Chunk.h"
#include "Math/Vec2.h"
#include "Rendering/Shaders/ChunkShader.h"
#include "Rendering/Shaders/PointShader.h"
#include "Math/Mat4x4.h"

class World{
public:
    World();
    ~World();

    void Init();
    void CleanUp();

    void Update();
    void Render();
    void RenderPoints();

    void OnWindowResizeEvent(int width, int height);

    void LoadViewMatrix(const Mat4x4& viewMatrix) const noexcept;

    Chunk* GetChunk(const Vec2<int16_t>& position);
    /// @brief force creates a chunk at that position and replaces old if there is one without freeing
    /// @return returns the newly allocated Chunk*
    Chunk* CreateChunk(const Vec2<int16_t>& position);
public:
    const ChunkShader& GetChunkShader() const noexcept{return m_ChunkShader;}
    const PointShader& GetPointShader() const noexcept{return m_PointShader;}
private:
    ChunkShader m_ChunkShader;
    PointShader m_PointShader;
    Mat4x4 m_Matrix;
    std::map<Vec2<int16_t>, Chunk*> m_Chunks;
};