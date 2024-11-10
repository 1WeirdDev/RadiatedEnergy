#include "pch.h"
#include "UIFrameShader.h"

#include "Core/Logger.h"
void UIFrameShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0)in vec2 vertex;\n \
    uniform mat4 projMatrix;\n \
    uniform vec2 uiScale;\n \
    uniform vec2 uiPos;\n \
    uniform int zIndex;\n \
    void main(){gl_Position = projMatrix * vec4(uiPos + (vertex * uiScale), 0.5 - (float(zIndex) / 100.0), 1);}";

    const char* fragmentShaderData = "#version 330 core\n \
    out vec4 color;\n \
    uniform vec3 uiColor;\n \
    void main(){color = vec4(uiColor, 1.0);}";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ScaleLocation = GetUniformLocation("uiScale");
    m_PositionLocation = GetUniformLocation("uiPos");
    m_ColorLocation = GetUniformLocation("uiColor");
    m_ZIndexLocation = GetUniformLocation("zIndex");
}

void UIFrameShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void UIFrameShader::LoadScale(float x, float y) const noexcept{
    LoadVector2(m_ScaleLocation, x, y);
}
void UIFrameShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}
void UIFrameShader::LoadColor(const Vec3<float>& color) const noexcept{
    LoadVector3(m_ColorLocation, color);
}

void UIFrameShader::LoadZIndex(int32_t zIndex) const noexcept{
    LoadInt(m_ZIndexLocation, zIndex);
}