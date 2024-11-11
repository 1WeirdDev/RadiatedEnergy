#pragma once

#include "../Scene.h"

#include "Rendering/Shaders/ChunkShader.h"
#include "World/Chunk.h"
#include "Math/Mat4x4.h"

class GameScene : public Scene{
public:
    GameScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;

    void HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key) override;
private:
    ChunkShader m_Shader;
    Chunk m_Chunk;
    Mat4x4 m_Matrix;
    Vec3<float> m_Position;
};