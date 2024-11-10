#pragma once

#include "../Shader.h"

class UIImageShader : public Shader{
public:
    UIImageShader(){}
    ~UIImageShader(){}
    //just default constructor all variables are on stack

    void Create();

    void LoadProjectionMatrix(float* data) const noexcept;
    void LoadScale(float x, float y) const noexcept;
    void LoadPosition(float x, float y) const noexcept;
    void LoadZIndex(int32_t zIndex) const noexcept;
private:
    GLint m_ProjMatrixLocation = -1;
    GLint m_ScaleLocation = -1;
    GLint m_PositionLocation = -1;
    GLint m_ZIndexLocation = -1;
};