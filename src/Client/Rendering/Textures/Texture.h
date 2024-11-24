#pragma once

#include <pch.h>

class Texture{
public:
    Texture(){}
    ~Texture(){}

    void LoadFromPath(const char* path);
    void CleanUp();

    void Bind() const noexcept;

    GLuint GetTextureId() const noexcept{return m_TextureId;}
    bool IsCreated() const noexcept{return m_IsCreated;}
private:
    GLuint m_TextureId = 0;
    bool m_IsCreated = false;
};