#include "pch.h"
#include "ChunkShader.h"

#include "Core/Logger.h"

void ChunkShader::Create()
{
    const char *vertexShaderData = "#version 330 core\n \
    layout(location = 0) in vec3 vertex;\n \
    layout(location = 1) in vec3 normal;\n \
    layout(location = 2) in int textureId;\n \
    struct UvData{\n \
        vec2 x;\n \
        vec2 y;\n \
        vec2 z;\n \
    };\n \
    out UvData uvCoords; \n \
    out vec3 uvNormal; \n \
    uniform mat4 projMatrix;\n \
    uniform mat4 viewMatrix;\n \
    uniform mat4 transformMatrix;\n \
    \
    void main(void){\n \
    uvCoords.x = vertex.zy + vec2(0, 0.5);\n \
    uvCoords.y = vertex.xz;\n \
    uvCoords.z = vertex.xy + vec2(0.5, 0);\n \
    uvNormal = normal; \
    gl_Position = projMatrix * viewMatrix * transformMatrix * vec4(vertex, 1.0);}";

    const char *fragmentShaderData = "#version 330 core\n \
    struct UvData{\n \
    vec2 x;\n \
    vec2 y;\n \
    vec2 z;\n \
    };\n \
    in UvData uvCoords;\n \
    in vec3 uvNormal;\n \
    out vec4 color;\n \
    uniform sampler2D imageTexture;\n \
    void main(){\
    vec3 normal = abs(normalize(uvNormal)); \
    //vec3 normal = absNormal / vec3(absNormal.x + absNormal.y + absNormal.z);\n \
    vec3 color1 = texture(imageTexture, uvCoords.x).rgb;\
    vec3 color2 = texture(imageTexture, uvCoords.y).rgb;\
    vec3 color3 = texture(imageTexture, uvCoords.z).rgb;\
    //color = vec4((color1 + color2 + color3) / 3, 1.0);\n \
    if(normal.x >= normal.z && normal.x >= normal.y){\
        color = vec4(color1, 1.0);\
    }else if(normal.z >= normal.x && normal.z >= normal.y){\
        color = vec4(color3, 1.0);\
    }\
    else{\
        color = vec4(color2, 1.0);\
    }\
    }";
    CreateWithSource(vertexShaderData, fragmentShaderData);

    Start();
    m_ProjMatrixLocation = GetUniformLocation("projMatrix");
    m_ViewMatrixLocation = GetUniformLocation("viewMatrix");
    m_TransformationMatrixLocation = GetUniformLocation("transformMatrix");
    CORE_DEBUG("Compiled Chunk Shader");
}
void ChunkShader::LoadProjectionMatrix(float *data) const noexcept
{
    LoadMat4x4(m_ProjMatrixLocation, data);
}
void ChunkShader::LoadViewMatrix(float *data) const noexcept
{
    LoadMat4x4(m_ViewMatrixLocation, data);
}
void ChunkShader::LoadTransformationMatrix(float *data) const noexcept
{
    LoadMat4x4(m_TransformationMatrixLocation, data);
}