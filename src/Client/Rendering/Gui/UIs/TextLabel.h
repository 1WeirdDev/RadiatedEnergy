#pragma once

#include "../UI.h"
#include "../Font.h"
#include "Math/Vec3.h"

class TextLabel : public UI{
public:
    TextLabel(class Gui* gui);
    TextLabel(class Gui* gui, Font* font);
    ~TextLabel();

    void SetFont(Font* font);
    void SetText(const char* text);

    //Updates the text render data
    void Update();
    void OnWindowResizeEvent(int width, int height) override;

    uint32_t GetCharacterRenderDataCount() const {return m_DataCount;}
    uint32_t GetStringLength() const {return m_StringLength;}
    uint32_t GetBufferSize() const {return m_BufferSize;}
    CharacterRenderData* GetCharacterRenderData() const {return m_RenderData;}
public:
    Font* GetFont() const {return m_Font;}
public:
    //TODO: Redo whole system
    Vec3<float> m_TextColor;
    unsigned char m_OverflowMode = UI_OM_Wrap;
    unsigned char m_HorizontalAlignmentMode = UI_HAM_Middle;
    unsigned char m_VerticalAlignmentMode = UI_VAM_Middle;
    bool text_scaled = true;  //Makes the text always fit the labels size, disabled multi lines
private:
    Font* m_Font = nullptr;

    std::string m_Text = "";
    uint32_t m_DataCount = 0;    //How much to draw
    uint32_t m_StringLength = 0;
    uint32_t m_BufferSize = 0;   //Size of draw buffer, gets reallocated if the new text size is larger than last
    CharacterRenderData* m_RenderData = nullptr;
};