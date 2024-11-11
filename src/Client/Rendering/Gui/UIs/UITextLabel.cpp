#include "pch.h"
#include "UITextLabel.h"
#include "Rendering/Window.h"
#include "Core/Logger.h"

UITextLabel::UITextLabel(class Gui* gui) : UI(gui), m_TextColor(0.0f, 0.0f, 0.0f){
    m_UIType = UIType::TextLabel; 
}
UITextLabel::UITextLabel(class Gui* gui, Font* font) : UI(gui) {
    m_UIType = UIType::TextLabel; 
    m_Font = font;
}
UITextLabel::~UITextLabel(){
    delete[] m_RenderData;
}

void UITextLabel::SetFont(Font* font){
    m_Font = font; 
    Update();
}
void UITextLabel::SetText(const char* text){
    m_Text = text;

    m_StringLength = m_Text.size();
    if(m_StringLength > m_BufferSize){
        //Reallocate buffer
        delete[] m_RenderData;
        m_RenderData = new CharacterRenderData[m_StringLength];
        m_BufferSize = m_StringLength;
    }

    m_DataCount = 0;
    Update();
}
void UITextLabel::Update(){
    if(m_Font == nullptr){
        CORE_WARN("Cant update text label without font");
        return;
    }
    Vec2<float> global_pos = GetGlobalPosition();
    Vec2<float> global_size = GetGlobalSize();

    float global_font_size = (float)m_Font->GetFontSize() / (float)Window::GetHeight();
    float pos_x = global_pos.m_X;
    float pos_y = global_pos.m_Y + global_size.m_Y - global_font_size;
    float row_width = 0.0f;

    float space_advance = 0;
    unsigned int last_row_start = 0;
    m_DataCount = 0;

    unsigned char row_count = 1;
    bool ignore_center = false;
    bool endedOnNewLine = false;
    for(unsigned int i = 0; i < m_StringLength; i++){
        char c = m_Text[i];
        GlyphCharacter glyph = m_Font->m_Characters.at(c);
        float advance = ((float)(glyph.m_AdvanceX)) / (float)Window::GetWidth();

        if(c == ' '){
            space_advance+= advance;
            continue;
        }else{
            //Spaces only matter if followed by character
            pos_x += space_advance;
            space_advance = 0;
            endedOnNewLine = false;
            if(pos_x + advance >= global_pos.m_X + global_size.m_X || c == '\n'){
                //Center last rows text
                float offset = (global_size.m_X - (row_width - global_pos.m_X));
                switch(m_HorizontalAlignmentMode){
                    case UI_HAM_Middle:{
                        offset /= 2.0f;
                    }
                }
                for(unsigned int s = last_row_start; s < m_DataCount; s++)
                    m_RenderData[s].m_PositionX += offset;
                if(c != '\n'){
                    if(m_OverflowMode == UI_OM_Cutoff){
                        ignore_center = true;
                        break;
                    }
                }

                endedOnNewLine = true;
                row_count++;

                pos_x = global_pos.m_X;
                pos_y -= global_font_size;
                last_row_start = m_DataCount;
                row_width = 0.0f;
            }

            if(c == '\n')continue;
            m_RenderData[m_DataCount].m_PositionX = pos_x + ((float)glyph.m_Bearing.m_X / (float)Window::GetWidth());
            m_RenderData[m_DataCount].m_PositionY = pos_y + ((float)glyph.m_Bearing.m_Y / (float)Window::GetHeight());
            m_RenderData[m_DataCount].m_Character = c;

            pos_x += advance;
            row_width = pos_x;
            m_DataCount++;
        }
    }
    if(endedOnNewLine)return;
    float offset = (global_size.m_X - (row_width - global_pos.m_X));
    switch(m_HorizontalAlignmentMode){
        case UI_HAM_Middle:{
            for(unsigned int s = last_row_start; s < m_DataCount; s++)
                m_RenderData[s].m_PositionX += offset / 2.0f;
        }
    }
    
    //Centering on y axis
    float font_global_height = ((float)(m_Font->GetFontSize() + 15) / (float)Window::GetHeight());
    offset = 0;
    switch(m_VerticalAlignmentMode){
        case UI_VAM_Middle:{
            offset = (global_size.m_Y - (font_global_height * ((float)row_count))) / 2.0f;// + font_global_height * (row_count - 1);
            break;
        }
        case UI_VAM_Bottom:{
            offset = (global_size.m_Y - (font_global_height * ((float)row_count)));// + font_global_height * (row_count - 1);
            break;
        }
    }
    for(uint32_t i = 0; i < m_DataCount; i++)
        m_RenderData[i].m_PositionY -= offset;
}
void UITextLabel::OnWindowResizeEvent(int width, int height){
    Update();
}