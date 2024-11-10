#pragma once

#include <pch.h>

class Texture{
public:
    Texture(){}
    ~Texture(){}

    void LoadFromPath(const char* path);
    void CleanUp();

    void Load() const noexcept;

private:
    GLuint m_TextureId = 0;
    bool m_IsCreated = false;
};