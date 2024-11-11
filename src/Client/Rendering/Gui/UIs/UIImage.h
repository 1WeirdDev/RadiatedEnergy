#pragma once

#include "../UI.h"

//#include "Rendering/Textures/Texture.h"

class UIImage : public UI{
public:
    UIImage(class Gui* gui);
    UIImage(class Gui* gui, GLuint texture);
    ~UIImage();
    
    void SetTextureId(GLuint texture){m_TextureId = texture;}
    GLuint GetTextureId() const noexcept{return m_TextureId;}
private:
    //Texture& m_Texture;
    GLuint m_TextureId = 0;
};