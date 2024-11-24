#pragma once

#include "../Scene.h"
#include "Entity/Player/Player.h"
#include "Rendering/Shaders/ChunkShader.h"
#include "World/World.h"
#include "Math/Mat4x4.h"
#include "Rendering/Gui/Gui.h"
#include "Rendering/Gui/UIs/UITextLabel.h"

class GameScene : public Scene{
public:
    GameScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;

    void OnWindowResizeEvent(int width, int height) override;
    void HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key) override;
private:
    Gui m_Gui;
    UITextLabel* m_TextLabel = nullptr;
    Player m_Player;
    ChunkShader m_Shader;
    World m_World;
    Mat4x4 m_Matrix;
    Vec3<float> m_Position;
    bool m_IsPolygonMode=false;
};