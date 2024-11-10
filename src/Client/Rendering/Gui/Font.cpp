#include <pch.h>
#include "Font.h"
#include "Core.h"

#include "UI.h"
#include "Core/Logger.h"
#include "UIDisplayManager.h"

Font::~Font()
{
    CleanUp();
}
void Font::CleanUp(){
    if(!m_IsLoaded)return;
    m_Shader.CleanUp();

    glDeleteBuffers(2, &m_SSBO_Id);

    if(m_TextureId == 0)return;
    glDeleteTextures(1, &m_TextureId);
    m_TextureId = 0;
}
void Font::LoadFont(const char *location)
{
    m_Location = location;
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        CORE_DEBUG("ERROR::FREETYPE: Could not init FreeType Library");
        MESSAGE_BOX("Freetype", "ERROR::FREETYPE: Could not init FreeType Library");
        std::exit(-1);
    }

    FT_Face face;
    if (FT_New_Face(ft, location, 0, &face))
    {
        CORE_DEBUG(("ERROR::FREETYPE: Failed to load font " + std::string(location)).c_str());
        MESSAGE_BOX("Freetype", "ERROR::FREETYPE: Failed to load font ");
        std::exit(-1);
    }

    FT_Set_Pixel_Sizes(face, 0, m_FontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    unsigned int image_width = m_FontSize * 10;
    unsigned char *data = new unsigned char[image_width * image_width];
    memset(data, 0, sizeof(unsigned char) * image_width * image_width);
    unsigned int x = 0;
    unsigned int y = 0;

    //Refered to https://learnopengl.com/In-Practice/Text-Rendering

    //So we write all the glyph data onto a single texture for a texture map
    for (unsigned char c = 0; c < 127; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            CORE_DEBUG("ERROR::FREETYTPE: Failed to load Glyph");
            MESSAGE_BOX("Freetype font", "ERROR::FREETYTPE: Failed to load Glyph");
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            break;
        }

        //In pixels
        int width = face->glyph->bitmap.width;
        int height = face->glyph->bitmap.rows;
        int bearing_x = face->glyph->bitmap_left;
        int bearing_y = -(m_FontSize - face->glyph->bitmap_top);
        float ratio = ((float)width / (float)m_FontSize);

        //Add one as a offset so there is no texture bleeding
        if (x + width + 1 >= image_width)
        {
            x = 0;
            y += m_FontSize + 1;
        }
        
        Vec2<float> pos((float)x / (float)image_width, (float)(y) / (float)image_width);
        Vec2<float> bearing((float)bearing_x, (float)bearing_y);

        for(unsigned char col = 0; col < height; col++){
            for(unsigned char row = 0; row < width; row++){
                data[(y + col) * image_width + x + width - row - 1] = face->glyph->bitmap.buffer[col * width + row];
            }
        }
        x+=width + 1;
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // bitshift by 6 to get value in pixels (2^6 = 64)
        GlyphCharacter character = {
            pos,
            bearing,
            ratio,
            face->glyph->advance.x >> 6,
            face->glyph->advance.y >> 6
        };

        m_Characters[c] = character;
    }
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        image_width,
        image_width,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        data);
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    m_Shader.Create();
    m_Shader.Start();
    UIDisplayManager::GetTexturedMesh().BindVao();
    
    //Bind to textured mesh from ui display manager
    //Create buffers
    glGenBuffers(2, &m_SSBO_Id);

    //We only care about the first 128 charcte
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO_Id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(CharacterDrawData) * 127 , nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBO_Id);
    glUniformBlockBinding(m_Shader.GetProgramId(), m_Shader.GetCharacterGlyphDatasLocation(), 0);
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_CRDB_Id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(CharacterRenderData) * TEXT_LABEL_MAX_CHAR_COUNT, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_CRDB_Id);
    glUniformBlockBinding(m_Shader.GetProgramId(), m_Shader.GetRenderDatasLocation(), 0);

    //Load them with data
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO_Id);
    CharacterDrawData* characterDrawData = (CharacterDrawData*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    
    // Fill the buffer with data
    for (unsigned char i = 0; i < 127; i++) {
        char c = i;
        characterDrawData[i].x = m_Characters.at(c).position.x;
        characterDrawData[i].y = m_Characters.at(c).position.y;
        characterDrawData[i].ratio = m_Characters.at(c).ratio;
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    CORE_INFO("Loaded font {0} from {1}", m_Name, location);
    m_IsLoaded = true;
}