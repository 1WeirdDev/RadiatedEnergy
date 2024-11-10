#include "pch.h"
#include "ChunkShader.h"

#include "Core/Logger.h"

void ChunkShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0) in vec3 vertex;\n \
    layout(location = 1) in int vertexColorIndex;\n \
    out vec3 vertexColor;\n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformationMatrix;\n \
    uniform vec2 position;\n \
    \
    uniform vec3 colors[3];\n \
    \
    void main(void){ \
    vertexColor = colors[vertexColorIndex];\n \
    gl_Position = projMatrix * viewMatrix * transformationMatrix * vec4(vertex, 1.0);}";

    const char* fragmentShaderData = "#version 330 core\n \
    in vec3 vertexColor;\n \
    out vec4 color; \
    void main(void){ \
        color = vec4(vertexColor, 1.0);\n \
    }";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformationMatrix");
    m_PositionLocation = GetUniformLocation("position");
    CORE_DEBUG("Compiled Chunk Shader");
}

void ChunkShader::LoadColor(int index, float x, float y, float z) const noexcept{
    GLint location = GetUniformLocation((std::string("colors[") + std::to_string(index) + "]").c_str());
    CORE_DEBUG("LOADING COLOR AT {0}", location);
    LoadVector3(location, x, y, z);
}
void ChunkShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void ChunkShader::LoadViewMatrix(float* data) const noexcept{
    LoadMat4x4(m_ViewMatrixLocation, data);
}
void ChunkShader::LoadTransformationMatrix(float* data) const noexcept{
    LoadMat4x4(m_TransformationMatrixLocation, data);
}
void ChunkShader::LoadPosition(float x, float y) const noexcept{
    LoadVector2(m_PositionLocation, x, y);
}