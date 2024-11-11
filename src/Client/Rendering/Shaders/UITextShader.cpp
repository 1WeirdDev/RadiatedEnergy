#include <pch.h>
#include "UITextShader.h"
#include "Core/Logger.h"

UITextShader::UITextShader(){}
UITextShader::~UITextShader(){}

void UITextShader::Create(){
    CreateWithSource("#version 450 core\n \
    uniform mat4 projectionMatrix; \n\
    uniform vec2 window_size; \n\
    uniform int zIndex; \n\
    uniform float fontSize; \n\
        \
    struct CharacterGlyphData{\
        float x;\
        float y;\
        float ratio;\
    };\
    struct RenderData{\
        float x; \
        float y; \
        int character;\
    };\
	layout(std430, binding = 0) buffer CharacterGlyphDatas{\
		CharacterGlyphData glyph_characters[127]; \
	};\
	layout(std430, binding = 1) buffer RenderDatas{\
		RenderData render_data[100]; \
	};\
    \
    layout(location = 0)in vec2 vertex; \
    layout(location = 1)in vec2 in_text_coord; \
    out vec2 textCoords; \
    void main(){ \
        vec2 position = vec2(render_data[gl_InstanceID].x, render_data[gl_InstanceID].y);\
        int index = render_data[gl_InstanceID].character; \
        vec2 char_tex_coords = vec2(glyph_characters[index].x, glyph_characters[index].y); \n \
        float ratio = glyph_characters[index].ratio;\n \
        float texture_atlas_width = fontSize * 10; \
        textCoords = char_tex_coords + (in_text_coord * vec2((fontSize * ratio) / texture_atlas_width, fontSize / texture_atlas_width)); \
        gl_Position = projectionMatrix * vec4(position + (vertex * vec2((fontSize * ratio) / window_size.x, (fontSize) / window_size.y)), -float(zIndex) / 100.0, 1.0);\
    }",//gl_Position = projectionMatrix * vec4(position + (vertex * vec2((fontSize * ratio) / window_size.x, (fontSize) / window_size.y)), 0.5 - (float(zIndex) / 100.0), 1.0);
    "#version 450 core\n \
    uniform sampler2D imageTexture; \
    uniform vec3 textColor; \
    in vec2 textCoords; \
    out vec4 outColor; \
    void main(){ \
        outColor = vec4(textColor, texture(imageTexture, textCoords).r); \
    }");
    //outColor = vec4(textColor, texture(imageTexture, textCoords).r); \

    Start();
    m_ProjectionMatrixLocation = GetUniformLocation("projectionMatrix");
    m_WindowSizeLocation = GetUniformLocation("window_size");
    m_ZIndexLocation = GetUniformLocation("zIndex");
    m_FontSizeLocation = GetUniformLocation("fontSize");
    m_TextColorLocation = GetUniformLocation("textColor");
    m_CharacterGlyphDatasLocation = GetUniformLocation("CharacterGlyphDatas");
    m_RenderDatasLocation = GetUniformLocation("RenderDatas");

}
void UITextShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjectionMatrixLocation, data);
}
void UITextShader::LoadWindowSize(float width, float height) const noexcept{
    LoadVector2(m_WindowSizeLocation, width, height);
}
void UITextShader::LoadZIndex(int zIndex) const noexcept{
    LoadInt(m_ZIndexLocation, zIndex);
}
void UITextShader::LoadFontSize(float fontSize) const noexcept{
    LoadFloat(m_FontSizeLocation, fontSize);
}
void UITextShader::LoadTextColor(float r, float g, float b) const noexcept{
    LoadVector3(m_TextColorLocation, r, g, b);
}