#pragma once

#include "Math/Mat4x4.h"
#include "Math/Vec3.h"

class Player{
public:
    Player();
    ~Player();
    
    void Update();
    void Draw() const;

    Vec3<float>& GetPosition() const noexcept{return (Vec3<float>&)m_Position;}
    Vec3<float>& GetRotation() const noexcept{return (Vec3<float>&)m_Rotation;}
    Mat4x4& GetViewMatrix() const noexcept{return (Mat4x4&)m_ViewMatrix;}
private:
    Vec3<float> m_Position;
    Vec3<float> m_Rotation;
    Mat4x4 m_ViewMatrix;
};