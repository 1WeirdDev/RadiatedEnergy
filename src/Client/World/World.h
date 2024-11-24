#pragma once

#include "pch.h"
#include "Chunk.h"
#include "Math/Vec2.h"
#include "Rendering/Shaders/ChunkShader.h"
#include "Rendering/Shaders/PointShader.h"
#include "Math/Mat4x4.h"
#include "Rendering/Textures/Texture.h"

class World{
public:
    World();
    ~World();

    void Init();
    void CleanUp();

    void Update();
    void BindTextures();
    void Render() noexcept;
    void RenderPoints() noexcept;

    void OnWindowResizeEvent(int width, int height);

    void LoadViewMatrix(const Mat4x4& viewMatrix) const noexcept;
    void LoadPointViewMatrix(const Mat4x4& viewMatrix) const noexcept;

    Chunk* GetChunk(const Vec2<int16_t>& position);
    /// @brief force creates a chunk at that position and replaces old if there is one without freeing
    /// @return returns the newly allocated Chunk*
    Chunk* CreateChunk(const Vec2<int16_t>& position);
public:
    const ChunkShader& GetChunkShader() const noexcept{return m_ChunkShader;}
#ifndef DIST
    const PointShader& GetPointShader() const noexcept{return m_PointShader;}
#endif
private:
    ChunkShader m_ChunkShader;
    Texture m_Texture;
    Mat4x4 m_Matrix;
    std::unordered_map<Vec2<int16_t>, Chunk*> m_Chunks;
private:
#ifndef DIST
    PointShader m_PointShader;
#endif
};