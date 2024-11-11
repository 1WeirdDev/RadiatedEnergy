#include "pch.h"
#include "ChunkShader.h"

#include "Core/Logger.h"

void ChunkShader::Create(){
    const char* vertexShaderData = "#version 330 core\n \
    layout(location = 0) in vec3 vertex;\n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformMatrix;\n \
    \
    void main(void){ \
    gl_Position = projMatrix * viewMatrix * transformMatrix * vec4(vertex, 1.0);}";

    const char* fragmentShaderData = "#version 330 core\n \
    out vec4 fragmentColor; \
    void main(void){ \
        fragmentColor = vec4(0.0, 1.0, 0.0, 1.0);\n \
    }";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformMatrix");
    CORE_DEBUG("Compiled Chunk Shader");
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