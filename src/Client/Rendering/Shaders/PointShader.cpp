#include "pch.h"
#include "PointShader.h"

#include "Core/Logger.h"

void PointShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0) in vec3 vertex;\n \
    layout(location = 1) in int enabled;\n \
    out vec3 pointColor;\n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformationMatrix;\n \
    uniform float scale;\n \
    uniform vec2 position;\n \
    void main(){\
    if(enabled > 0)pointColor = vec3(1.0, 1.0, 1.0);\
    else pointColor = vec3(0.0, 0.0, 0.0); \
    gl_Position = projMatrix * viewMatrix * transformationMatrix * vec4(vertex, 1.0);}";

    const char* fragmentShaderData = "#version 330 core\n \
    in vec3 pointColor; \n \
    out vec4 color;\n \
    void main(){color = vec4(pointColor, 1.0);}";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformationMatrix");
    m_ScaleLocation = GetUniformLocation("scale");
    m_PositionLocation = GetUniformLocation("position");
}

void PointShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void PointShader::LoadViewMatrix(float* data) const noexcept{
    LoadMat4x4(m_ViewMatrixLocation, data);
}
void PointShader::LoadTransformationMatrix(float* data) const noexcept{
    LoadMat4x4(m_TransformationMatrixLocation, data);
}
void PointShader::LoadScale(float value) const noexcept{
    LoadFloat(m_ScaleLocation, value);
}
void PointShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}