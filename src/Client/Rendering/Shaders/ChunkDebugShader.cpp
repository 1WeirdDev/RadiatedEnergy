#include "pch.h"
#include "ChunkDebugShader.h"

#include "Core/Logger.h"

void ChunkDebugShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0) in vec3 vertex;\n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformationMatrix;\n \
    uniform vec2 position;\n \
    \
    uniform vec3 colors[3];\n \
    \
    void main(void){ \
    gl_Position = projMatrix * viewMatrix * transformationMatrix * vec4(vertex, 1.0);}";

    const char* fragmentShaderData = "#version 330 core\n \
    out vec4 color; \
    void main(void){ \
        color = vec4(1.0, 0.0, 0.0, 1.0);\n \
    }";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformationMatrix");
    m_PositionLocation = GetUniformLocation("position");
    CORE_DEBUG("Compiled Chunk Debug Shader");
}

void ChunkDebugShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void ChunkDebugShader::LoadViewMatrix(float* data) const noexcept{
    LoadMat4x4(m_ViewMatrixLocation, data);
}
void ChunkDebugShader::LoadTransformationMatrix(float* data) const noexcept{
    LoadMat4x4(m_TransformationMatrixLocation, data);
}
void ChunkDebugShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}