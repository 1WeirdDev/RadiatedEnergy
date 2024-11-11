#include "pch.h"
#include "GameScene.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Input/Keyboard.h"
#include "Rendering/Window.h"
#include "Math/MatrixUtils.h"
#include "Game.h"

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
    m_Shader.Create();
    MatrixUtils::TranslateMat4x4(m_Matrix.GetData(), Vec3<float>(0,0, -5));
    m_Shader.LoadTransformationMatrix(m_Matrix.GetData());
    m_Matrix.SetIdentity();
    MatrixUtils::CreatePerspectiveProjection(m_Matrix.GetData(), MatrixUtils::ToRadians(90.0f), Window::GetAspectRatio(), 0.01f, 1000.0f);
    m_Shader.LoadProjectionMatrix(m_Matrix.GetData());
    m_Chunk.CreateMesh();
}

void GameScene::CleanUp(){
    m_Shader.CleanUp();
}
void GameScene::Update(){
    if(Keyboard::IsKeyDown(GLFW_KEY_W)){
        m_Position.m_X-=sin(0) * Time::GetDeltaTime();
        m_Position.m_Z+=cos(0) * Time::GetDeltaTime();
    }
    if(Keyboard::IsKeyDown(GLFW_KEY_S)){
        m_Position.m_X+=sin(0) * Time::GetDeltaTime();
        m_Position.m_Z-=cos(0) * Time::GetDeltaTime();
    }
}
void GameScene::Draw(){
    m_Shader.Start();
    m_Matrix.SetIdentity();
    MatrixUtils::TranslateMat4x4(m_Matrix.GetData(), m_Position);
    m_Shader.LoadViewMatrix(m_Matrix.GetData());
    m_Chunk.Draw();
}
void GameScene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){

}