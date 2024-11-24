#include "pch.h"
#include "World.h"
#include "Math/MatrixUtils.h"
#include "Rendering/Window.h"
#include "Core/Logger.h"

World::World(){}
World::~World(){}

void World::Init(){
    m_ChunkShader.Create();
    MatrixUtils::CreatePerspectiveProjection(m_Matrix.GetData(), MatrixUtils::ToRadians(90.0f), Window::GetAspectRatio(), 0.01f, 1000.0f);
    m_ChunkShader.LoadProjectionMatrix(m_Matrix.GetData());
#ifndef DIST
    m_PointShader.Create();
    m_PointShader.Start();
    m_PointShader.LoadProjectionMatrix(m_Matrix.GetData());
    m_PointShader.LoadDivisor(Chunk::s_PointDivisor);
    m_ChunkShader.Start();
#endif
    m_Matrix.SetIdentity();
    //MatrixUtils::TranslateMat4x4(m_Matrix.GetData(), Vec3<float>(0,0, -5));
    m_ChunkShader.LoadTransformationMatrix(m_Matrix.GetData());

    for(size_t x = 0; x < 5; x++){
        for(size_t z = 0; z < 5; z++){
            CreateChunk(Vec2<int16_t>(x, z));
        }
    }
}
void World::CleanUp(){
    for (const auto &myPair : m_Chunks)
        delete myPair.second;
    m_ChunkShader.CleanUp();
}
void World::Update(){
}
void World::Render(){
    m_Matrix.SetIdentity();
    MatrixUtils::CreateScalingMatrix(m_Matrix.GetData(), 0.5f, 0.5f, 0.5f);
    for (const auto &myPair : m_Chunks) {
        if(myPair.second == nullptr)continue;

        //TODO: maybe see if creating a global positon on the chunk then accessing that would be faster than mulitplying
        const Vec2<int16_t>& position = myPair.first;
        Chunk* chunk = myPair.second;
        MatrixUtils::CreateTranslationMatrix(m_Matrix.GetData(), 0.5f * (position.m_X* Chunk::s_ChunkWidth), 0, 0.5f * (position.m_Y * Chunk::s_ChunkWidth));

        m_ChunkShader.LoadTransformationMatrix(m_Matrix.GetData());
        chunk->Draw();
    }
}
void World::RenderPoints(){
    
    for (const auto &myPair : m_Chunks) {
        if(myPair.second == nullptr)continue;

        //TODO: maybe see if creating a global positon on the chunk then accessing that would be faster than mulitplying
        const Vec2<int16_t>& position = myPair.first;
        Chunk* chunk = myPair.second;
        MatrixUtils::CreateTranslationMatrix(m_Matrix.GetData(), position.m_X* Chunk::s_ChunkWidth, 0, position.m_Y * Chunk::s_ChunkWidth);
        //MatrixUtils::CreateTranslationMatrixXZ<int32_t>(m_Matrix.GetData(), chunk->GetGlobalPosition());
        m_PointShader.LoadTransformationMatrix(m_Matrix.GetData());
        chunk->DrawPoints();
    }
}
Chunk* World::GetChunk(const Vec2<int16_t>& position){
    auto i = m_Chunks.find(position);
    if(i == m_Chunks.end())return nullptr;
    return i->second;
}
Chunk* World::CreateChunk(const Vec2<int16_t>& position){
    Chunk* chunk = new Chunk(position);
    //m_Chunks[position] = chunk;
    m_Chunks.emplace(position, chunk);
    chunk->CreateBlockData();
    chunk->CreateMeshData();
    chunk->CreateMesh();
    return chunk;
}

void World::LoadViewMatrix(const Mat4x4& viewMatrix) const noexcept{
    m_ChunkShader.LoadViewMatrix(viewMatrix.GetData());
}

void World::LoadPointViewMatrix(const Mat4x4& viewMatrix) const noexcept{
    m_PointShader.LoadViewMatrix(viewMatrix.GetData());
}
void World::OnWindowResizeEvent(int width, int height){
    m_ChunkShader.Start();
    MatrixUtils::CreatePerspectiveProjection(m_Matrix.GetData(), MatrixUtils::ToRadians(90.0f), (float)width / (float)height, 0.01f, 1000.0f);
    m_ChunkShader.LoadProjectionMatrix(m_Matrix.GetData());
#ifndef DIST
    m_PointShader.Start();
    m_PointShader.LoadProjectionMatrix(m_Matrix.GetData());
#endif
    m_Matrix.SetIdentity();
}