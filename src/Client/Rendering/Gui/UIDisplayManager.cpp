#include "pch.h"
#include "UIDisplayManager.h"

#include "UI.h"
#include "Core/Logger.h"
#include "Rendering/Window.h"
#include "Math/MatrixUtils.h"
#include "Rendering/Gui/UIs/Image.h"
#include "Rendering/Gui/UIs/Frame.h"
#include "Rendering/Gui/UIs/TextLabel.h"

UIFrameShader UIDisplayManager::s_FrameShader;
UIImageShader UIDisplayManager::s_ImageShader;
BasicMesh UIDisplayManager::s_BasicMesh;
TexturedMesh UIDisplayManager::s_TexturedMesh;

Mat4x4 UIDisplayManager::s_ProjMatrix;
std::vector<Font*> UIDisplayManager::s_Fonts;
Texture UIDisplayManager::s_Texture;

void UIDisplayManager::Init(){
    //Create UI Meshes
    uint8_t vertices[8]{
        0,0,
        0,1,
        1,0,
        1,1
    };

    uint8_t indices[6]{
        0,1,2,2,1,3
    };

    uint8_t textureCoords[8]{
        1,1,
        1,0,
        0,1,
        0,0
    };
    s_BasicMesh.Create(2, VT_UINT8, FT_UINT8, &vertices, &indices, 8, 6);
    s_TexturedMesh.Create(2, VT_UINT8, FT_UINT8, VT_UINT8, &vertices, &indices, &textureCoords, 8, 6, 8);
    
    MatrixUtils::CreateOrthoProjection(s_ProjMatrix.GetData(), 0.0f, 1.0f, 0, 1, 1, 0);

    s_FrameShader.Create();
    s_FrameShader.Start();
    s_FrameShader.LoadProjectionMatrix(s_ProjMatrix.GetData());

    s_ImageShader.Create();
    s_ImageShader.Start();
    s_ImageShader.LoadProjectionMatrix(s_ProjMatrix.GetData());

    Font* font = CreateFont("Arial", "res/Fonts/Arial.ttf");
    CreateFont("RobotoRegular", "res/Fonts/Roboto-Regular.ttf");
    s_Texture.LoadFromPath("res/Textures/test.png");
}

void UIDisplayManager::Shutdown(){
    s_FrameShader.CleanUp();
    s_ImageShader.CleanUp();

    //Cleanup fonts before meshes since fonts use the textured mesh buffers
    for(size_t i = 0; i < s_Fonts.size(); i++){
        s_Fonts[i]->CleanUp();
        delete s_Fonts[i];
    }
    s_BasicMesh.CleanUp();
    s_TexturedMesh.CleanUp();

    s_Fonts.resize(0);
}

void UIDisplayManager::OnWindowResizeEvent(int width, int height){
    //Load window size to font shaders
    for(size_t i = 0; i < s_Fonts.size(); i++){
        UITextShader& shader = s_Fonts[i]->GetShader();
        shader.Start();
        shader.LoadWindowSize(width, height);
    }
}
void UIDisplayManager::DrawUI(UI* ui, int zIndex){
    Vec2<float>& globalPosition = ui->GetGlobalPosition();
    Vec2<float>& globalSize = ui->GetGlobalSize();

    //CORE_DEBUG("Global ui pos {0} {1}", globalPosition.x, globalPosition.y);

    if(!ui->m_Visible){
        zIndex+=2;
        const std::vector<UI*>& children = ui->GetChildren();
        for (UI* childUI : children){
            DrawUI(childUI, zIndex);
        }
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    //s_Texture.Load();
    switch(ui->GetUIType()){
    case UT_Frame:{
        s_FrameShader.Start();
        s_FrameShader.LoadScale(globalSize.x, globalSize.y);
        s_FrameShader.LoadPosition(globalPosition.x, globalPosition.y);
        s_FrameShader.LoadColor(((Frame&)*ui).m_Color);
        s_FrameShader.LoadZIndex(zIndex);
        s_BasicMesh.Draw();
        break;
    }
    case UT_Image:{
        s_ImageShader.Start();
        s_ImageShader.LoadScale(globalSize.x, globalSize.y);
        s_ImageShader.LoadPosition(globalPosition.x, globalPosition.y);
        s_ImageShader.LoadZIndex(zIndex);
        glBindTexture(GL_TEXTURE_2D, ((Image*)ui)->GetTextureId());
        s_TexturedMesh.Draw();
        break;
    }
    case UT_TextLabel:{
        TextLabel* textLabel = (TextLabel*)ui;
        Font* font = textLabel->GetFont();

        if(font == nullptr){
            break;
        }
        //CORE_DEBUG("DRAWING TEXT LABEL");
        UITextShader& shader = font->GetShader();

        shader.Start();
        uint16_t fontSize = font->GetFontSize();
        shader.Start();
        shader.LoadFontSize(fontSize);
        shader.LoadZIndex(zIndex + textLabel->m_ZIndex);
        shader.LoadTextColor(textLabel->m_TextColor.x, textLabel->m_TextColor.y, textLabel->m_TextColor.z);
        glBindTexture(GL_TEXTURE_2D, font->GetTextureId());
        uint32_t count = textLabel->GetCharacterRenderDataCount();
        CharacterRenderData* data = textLabel->GetCharacterRenderData();

        if(count == 0 || data == nullptr)break;
        s_TexturedMesh.BindVao();
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, font->GetCRDBId());
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(CharacterRenderData) * count, data);
        s_TexturedMesh.DrawInstancedNoBinding(count);
    }
    default:
        break;
    }
    zIndex+=2;
    const std::vector<UI*>& children = ui->GetChildren();
    for (UI* childUI : children){
        DrawUI(childUI, zIndex);
    }
}

Font* UIDisplayManager::GetFont(const char* fontName){
    for(size_t i = 0; i < s_Fonts.size(); i++){
        size_t size = strlen(fontName);
        size_t fontSize = strlen(s_Fonts[i]->GetName());
        if(fontSize < size)size = fontSize;
        if(strncmp(s_Fonts[i]->GetName(), fontName, size) == 0){
            return s_Fonts[i];
        }
    }
    return nullptr;
}
Font* UIDisplayManager::CreateFont(const char* fontName, const char* fontPath){
    Font* font = new Font(fontName);
    font->LoadFont(fontPath);

    //Load ProjectionMatrix
    UITextShader& shader = font->GetShader();
    //CORE_DEBUG("TExt shader {0} {1} {2}", shader.GetProgramId(), shader.GetVertexShaderId(), shader.GetFragmetnShaderId());
    shader.Start();
    //Load Projection matrix this only needs to be done once
    shader.LoadProjectionMatrix(UIDisplayManager::s_ProjMatrix.GetData());

    //Load Window Size while we are at it
    shader.LoadWindowSize(Window::GetWidth(), Window::GetHeight());
    s_Fonts.push_back(font);
    return font;
}