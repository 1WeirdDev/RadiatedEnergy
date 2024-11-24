#include "pch.h"
#include "GameScene.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Input/Keyboard.h"
#include "Rendering/Window.h"
#include "Rendering/Gui/UIs/UIFrame.h"
#include "Math/MatrixUtils.h"
#include "Game.h"
#include "Rendering/Gui/UIDisplayManager.h"

GameScene::GameScene(){}
void GameScene::Init(){
    Game::GetClient()->SetPacketReceivedCallback([](Packet& packet){
        CORE_DEBUG("CALLED RECDEIVED CALLBVACK");
        uint32_t packetSize = packet.ReadInt32();
        packet.ReadInt8();
        std::string data = packet.ReadString();
        CORE_DEBUG("PACKET LENGTH {0} , data {1}", packetSize, data);

        Packet sendPacket;
        sendPacket.PrepareWrite();
        sendPacket.WriteString("Welcome From Client");
        Game::GetClient()->SendTCPPacket(std::move(sendPacket));
    });
    Game::GetClient()->Connect("127.0.0.1", 8888);

    /*
    m_Shader.Create();
    
    MatrixUtils::CreatePerspectiveProjection(m_Matrix.GetData(), MatrixUtils::ToRadians(90.0f), Window::GetAspectRatio(), 0.01f, 1000.0f);
    m_Shader.LoadProjectionMatrix(m_Matrix.GetData());
    m_Matrix.SetIdentity();
    //MatrixUtils::TranslateMat4x4(m_Matrix.GetData(), Vec3<float>(0,0, -5));
    m_Shader.LoadTransformationMatrix(m_Matrix.GetData());
    m_Chunk.CreateMeshData();
    m_Chunk.CreateMesh();
    */

    m_World.Init();
    UIFrame* frame = m_Gui.CreateChild<UIFrame>();
    frame->SetPosition(0, 0.5f, 0, 0);
    frame->SetSize(0.5f, 0.5f, 0, 0);
    frame->SetVisible(false);

    m_TextLabel = frame->CreateChild<UITextLabel>(UIDisplayManager::GetFont("RobotoRegular"));
    Font* font = UIDisplayManager::GetFont("RobotoRegular");
    m_TextLabel->SetFont(font);
    m_TextLabel->SetPosition(0, 0, 0, font->GetFontSize());
    m_TextLabel->SetSize(1.0f, 0, 0, font->GetFontSize());

}

void GameScene::CleanUp(){
    m_Gui.CleanUp();
    m_World.CleanUp();
    m_Shader.CleanUp();
}
void GameScene::Update(){
    m_Player.Update();
    Vec3<float> position = m_Player.GetPosition();
    m_TextLabel->SetText(("POSITION " + std::to_string((int)position.m_X) + " " + std::to_string((int)position.m_Y) + " " + std::to_string((int)position.m_Z)).c_str());
}
void GameScene::Draw(){
    m_Gui.Draw();
    const ChunkShader& chunkShader = m_World.GetChunkShader();
    
#ifndef DIST
    const PointShader& pointShader = m_World.GetPointShader();
    chunkShader.Start();
    
    glPolygonMode(GL_FRONT_AND_BACK, m_IsPolygonMode ? GL_LINE : GL_FILL);
    if(m_IsPolygonMode){
        glDisable(GL_CULL_FACE);
        m_World.LoadViewMatrix(m_Player.GetViewMatrix());
        m_World.BindTextures();
        m_World.Render();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        pointShader.Start();
        m_World.LoadPointViewMatrix(m_Player.GetViewMatrix());
        m_World.RenderPoints();
    }else{
        glEnable(GL_CULL_FACE);
        m_World.LoadViewMatrix(m_Player.GetViewMatrix());
        m_World.BindTextures();
        m_World.Render();
    }
    glEnable(GL_CULL_FACE);
#else
    m_World.LoadViewMatrix(m_Player.GetViewMatrix());
    m_World.BindTextures();
    m_World.Render();
#endif
}

void GameScene::OnWindowResizeEvent(int width, int height){
    m_World.OnWindowResizeEvent(width, height);
}
void GameScene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){
#ifndef DIST
    if(key == GLFW_KEY_R && state == KeyState::Pressed){
        m_IsPolygonMode = !m_IsPolygonMode;
    }
#endif
}