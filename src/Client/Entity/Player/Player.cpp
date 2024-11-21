#include "pch.h"
#include "Player.h"
#include "Math/MatrixUtils.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Core/Time.h"
#include "Core/Logger.h"

Player::Player(){}
Player::~Player(){}

void Player::Update(){
    m_Rotation.m_Z += Mouse::GetDeltaY() * 0.0025f;
    m_Rotation.m_Y += Mouse::GetDeltaX() * 0.0025f;
    if(Keyboard::IsKeyDown(GLFW_KEY_W)){
        m_Position.m_X+=sin(m_Rotation.m_Y) * Time::GetDeltaTime();
        m_Position.m_Z-=cos(m_Rotation.m_Y) * Time::GetDeltaTime();
    }
    if(Keyboard::IsKeyDown(GLFW_KEY_S)){
        m_Position.m_X-=sin(m_Rotation.m_Y) * Time::GetDeltaTime();
        m_Position.m_Z+=cos(m_Rotation.m_Y) * Time::GetDeltaTime();
    }
    if(Keyboard::IsKeyDown(GLFW_KEY_A)){
        m_Position.m_X+=sin(m_Rotation.m_Y - MatrixUtils::ToRadians(90.0f)) * Time::GetDeltaTime();
        m_Position.m_Z-=cos(m_Rotation.m_Y - MatrixUtils::ToRadians(90.0f)) * Time::GetDeltaTime();
    }
    if(Keyboard::IsKeyDown(GLFW_KEY_D)){
        m_Position.m_X-=sin(m_Rotation.m_Y - MatrixUtils::ToRadians(90.0f)) * Time::GetDeltaTime();
        m_Position.m_Z+=cos(m_Rotation.m_Y - MatrixUtils::ToRadians(90.0f)) * Time::GetDeltaTime();
    }

    if(Keyboard::IsKeyDown(GLFW_KEY_SPACE))
        m_Position.m_Y += Time::GetDeltaTime();
    if(Keyboard::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
        m_Position.m_Y -= Time::GetDeltaTime();
    //CORE_DEBUG("M_POSITION {0} {1} {2}", m_Position.m_X, 0, m_Position.m_Z);
    m_ViewMatrix.SetIdentity();
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.m_Z, Vec3<float>(1,0,0));
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.m_Y, Vec3<float>(0,1,0));
    MatrixUtils::RotateMat4x4(m_ViewMatrix.GetData(), m_Rotation.m_X, Vec3<float>(0,0,1));
    MatrixUtils::TranslateMat4x4<float>(m_ViewMatrix.GetData(), -m_Position);
    
}
void Player::Draw() const{

}