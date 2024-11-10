#pragma once

#include "../Shader.h"

class UITextShader : public Shader{
public:
    UITextShader();
    ~UITextShader();

    void Create();
    
    void LoadProjectionMatrix(float* data) const noexcept;
    void LoadWindowSize(float width, float height) const noexcept;
    void LoadZIndex(int value) const noexcept;
    void LoadScale(float value) const noexcept;
    void LoadFontSize(float font_size) const noexcept;
    void LoadTextColor(float r, float g, float b) const noexcept;
public:
    int GetProjectionMatrixLocation() const noexcept{return m_ProjectionMatrixLocation;}
    int GetWindowSizeLocation() const noexcept{return m_WindowSizeLocation;}
    int GetZIndexLocation() const noexcept{return m_ZIndexLocation;}
    int GetScaleLocation() const noexcept{return m_ScaleLocation;}
    int GetFontSizeLocation() const noexcept{return m_FontSizeLocation;}
    int GetTextColorLocation() const noexcept{return m_TextColorLocation;}
    int GetCharacterGlyphDatasLocation() const noexcept{return m_CharacterGlyphDatasLocation;}
    int GetRenderDatasLocation() const noexcept {return m_RenderDatasLocation;}
private:
    GLint m_ProjectionMatrixLocation = -1;
    GLint m_WindowSizeLocation = -1;
    GLint m_ZIndexLocation = -1;
    GLint m_ScaleLocation = -1;
    GLint m_FontSizeLocation = -1;
    GLint m_TextColorLocation = -1;
    GLint m_CharacterGlyphDatasLocation = -1;
    GLint m_RenderDatasLocation = -1;
};