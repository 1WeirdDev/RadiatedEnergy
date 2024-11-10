#include "pch.h"
#include "UIImageShader.h"

#include "Core/Logger.h"
void UIImageShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0)in vec2 vertex;\n \
    layout(location = 1)in vec2 textureCoord;\n \
    uniform mat4 projMatrix;\n \
    uniform vec2 uiScale;\n \
    uniform vec2 uiPos;\n \
    uniform int zIndex;\n \
    \
    out vec2 textureCoords;\n \
    void main(){\n \
    textureCoords = textureCoord;\
    gl_Position = projMatrix * vec4(uiPos + (vertex * uiScale), 0.5 - (float(zIndex) / 100.0), 1);}";

    const char* fragmentShaderData = "#version 330 core\n \
    in vec2 textureCoords;\n \
    out vec4 color;\n \
    uniform sampler2D imageTexture;\n \
    void main(){\
    color = texture(imageTexture, textureCoords);}";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ScaleLocation = GetUniformLocation("uiScale");
    m_PositionLocation = GetUniformLocation("uiPos");
    m_ZIndexLocation = GetUniformLocation("zIndex");
}

void UIImageShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void UIImageShader::LoadScale(float x, float y) const noexcept{
    LoadVector2(m_ScaleLocation, x, y);
}
void UIImageShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}

void UIImageShader::LoadZIndex(int32_t zIndex) const noexcept{
    LoadInt(m_ZIndexLocation, zIndex);
}