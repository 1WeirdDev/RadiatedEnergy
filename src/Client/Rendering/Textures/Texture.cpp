#include "pch.h"
#include "Texture.h"

#include "Core/Logger.h"

//STB
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


void Texture::LoadFromPath(const char* path){
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    int width, height, nrChannels;
    uint8_t *data = stbi_load(path, &width, &height, &nrChannels, 3); 

    if(!data){
        CORE_WARN("Failed to load texture {0}. Creating test texture", path);
        width = 1024;
        height = 1024;
        nrChannels = 3;
        data = (uint8_t*)malloc(sizeof(uint8_t) * width * height);
        for(uint16_t x = 0; x < width; x++){
            for(uint16_t y = 0; y < height; y++){
                uint32_t i = ((x * height) + y) * 3;
                data[i] = 1;
                data[i + 2] = 1;
            }
        }
    }else{
        CORE_DEBUG("Loaded texture \"{0}\"", path);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_IsCreated = false;
}

void Texture::CleanUp(){
    if(!m_IsCreated)return;
    glDeleteTextures(1, &m_TextureId);
}

void Texture::Load() const noexcept {
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}