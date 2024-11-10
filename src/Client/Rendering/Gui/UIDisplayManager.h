#pragma once

#include "Rendering/Mesh/BasicMesh.h"
#include "Rendering/Mesh/TexturedMesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Shaders/UIFrameShader.h"
#include "Rendering/Shaders/UIImageShader.h"
#include "Rendering/Shaders/UITextShader.h"
#include "Math/Mat4x4.h"
#include "Rendering/Textures/Texture.h"

#include "Font.h"

/*
class FontMaterial{
public:
    Font* m_Font;
    GLuint m_SSBO_Id;   //Shader Storage Buffer Object
    GLuint m_CRDB_Id;   //Character Render Data Buffer
};*/

class UIDisplayManager{
public:
    static void Init();
    static void Shutdown();

    static void OnWindowResizeEvent(int width, int height);
    static void DrawUI(class UI* ui, int z_index);

    static Font* CreateFont(const char* fontName, const char* fontPath);
    static Font* GetFont(const char* fontName);
public:
    static TexturedMesh& GetTexturedMesh() noexcept {return s_TexturedMesh;}
    static float* GetProjectionMatrix() noexcept{return s_ProjMatrix.GetData();}
private:
    static UIFrameShader s_FrameShader;
    static UIImageShader s_ImageShader;
    static BasicMesh s_BasicMesh;
    static TexturedMesh s_TexturedMesh;

    static Mat4x4 s_ProjMatrix;
    static Texture s_Texture;

    static std::vector<Font*> s_Fonts;
};