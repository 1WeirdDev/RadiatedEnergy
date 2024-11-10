#include <pch.h>
#include "UITextShader.h"

UITextShader::UITextShader(){}
UITextShader::~UITextShader(){}

void UITextShader::Create(){
    CreateWithSource("#version 450 core\n \
    uniform mat4 projection_matrix; \n\
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
    out vec2 text_coords; \
    void main(){ \
        vec2 position = vec2(render_data[gl_InstanceID].x, render_data[gl_InstanceID].y);\
        int index = render_data[gl_InstanceID].character; \
        vec2 char_tex_coords = vec2(glyph_characters[index].x, glyph_characters[index].y); \n \
        float ratio = glyph_characters[index].ratio;\n \
        float texture_atlas_width = fontSize * 10; \
        text_coords = char_tex_coords + (in_text_coord * vec2((fontSize * ratio) / texture_atlas_width, fontSize / texture_atlas_width)); \
        gl_Position = projection_matrix * vec4(position + (vertex * vec2((fontSize * ratio) / window_size.x, (fontSize) / window_size.y)), 0.5 - (float(zIndex) / 100.0), 1.0); \
    }",
    "#version 450 core\n \
    uniform sampler2D image_texture; \
    uniform vec3 text_color; \
    in vec2 text_coords; \
    out vec4 out_color; \
    void main(){ \
        out_color = vec4(text_color, texture(image_texture, text_coords).r); \
    }");
    
    m_ProjectionMatrixLocation = GetUniformLocation("projection_matrix");
    m_WindowSizeLocation = GetUniformLocation("window_size");
    m_ZIndexLocation = GetUniformLocation("zIndex");
    m_FontSizeLocation = GetUniformLocation("fontSize");
    m_TextColorLocation = GetUniformLocation("text_color");
    m_CharacterGlyphDatasLocation = GetUniformLocation("CharacterGlyphDatas");
    m_RenderDatasLocation = GetUniformLocation("RenderDatas");
}
void UITextShader::LoadProjectionMatrix(float* data) const noexcept{
    LoadMat4x4(m_ProjectionMatrixLocation, data);
}
void UITextShader::LoadWindowSize(float width, float height) const noexcept{
    LoadVector2(m_WindowSizeLocation, width, height);
}
void UITextShader::LoadZIndex(int z_index) const noexcept{
    LoadInt(m_ZIndexLocation, z_index);
}
void UITextShader::LoadFontSize(float font_size) const noexcept{
    LoadFloat(m_FontSizeLocation, font_size);
}
void UITextShader::LoadTextColor(float r, float g, float b) const noexcept{
    LoadVector3(m_TextColorLocation, r, g, b);
}