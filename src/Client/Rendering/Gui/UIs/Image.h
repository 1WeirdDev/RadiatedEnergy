#pragma once

#include "../UI.h"

//#include "Rendering/Textures/Texture.h"

class Image : public UI{
public:
    Image(class Gui* gui);
    Image(class Gui* gui, GLuint texture);
    ~Image();
    
    void SetTextureId(GLuint texture){m_TextureId = texture;}
    GLuint GetTextureId() const noexcept{return m_TextureId;}
private:
    //Texture& m_Texture;
    GLuint m_TextureId = 0;
};