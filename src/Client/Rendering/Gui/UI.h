#pragma once

#include "pch.h"
#include "Math/Vec2.h"
#include "Math/UDim2.h"

#define TEXT_LABEL_MAX_CHAR_COUNT 100
enum UIType{
    UT_None= 0,
    UT_Frame,
    UT_Button,
    UT_Image,
    UT_TextLabel
};

enum ScreenSizeRestraint{
    SSR_None = 0,
    SSR_AspectRatioX,
    SSR_AspectRatioY,
    SSR_InverseAspectRatioX,
    SSR_InverseAspectRatioY
};

enum OverflowMode{
    UI_OM_None = 0U,
    UI_OM_Wrap,
    UI_OM_Cutoff
};

enum TextHorizontalAlignmentMode{
    UI_HAM_Left=0,
    UI_HAM_Middle,
    UI_HAM_Right
};

enum TextVerticalAlignmentMode{
    UI_VAM_Top=0,
    UI_VAM_Middle,
    UI_VAM_Bottom
};
struct CharacterRenderData{
    float m_PositionX = 0;//Relative
    float m_PositionY = 0;
    GLint m_Character = 0;  //type is int in glsl
};

struct CharacterDrawData{
    float x;
    float y;
    float ratio;
};

class Gui;
class UI{
public:
    friend Gui;
    UI(Gui* gui);
    virtual ~UI();

    //calculates the relative position needed to be at that global position
    void SetGlobalPosition(float scaleX, float scaleY, uint16_t offsetX, uint16_t offsetY);
    void SetPosition(float scaleX, float scaleY, uint16_t offsetX, uint16_t offsetY);
    void SetSize(float scaleX, float scaleY, uint16_t offsetX, uint16_t offsetY);

    template <typename ChildType, typename ...Arg>
    ChildType* CreateChild(Arg... args){
        ChildType* child = new ChildType(m_Gui, args...);
        child->m_Parent = this;
        child->m_Gui = m_Gui;
        child->CalculateGlobalData();
        m_Children.push_back(child);
        return child;
    }

    UI* GetChild(size_t index) const;

    /// @brief if the specified ui* is found as a child we remove it from the child list without freeing int
    /// @param ui the UI* that we are removing
    void RemoveChild(UI* ui);

    /// @brief We search through the children and if we find the ui specified we remove and free its memory
    /// @param ui the UI* we are searching to delete
    void DeleteChild(UI* ui);
    /// @brief calls the deconstructor and frees all of the children while resizing children
    void DeleteChildren();
    //Events
public:
    virtual void OnWindowResizeEvent(int width, int height){}
    /// @brief Will update the members global size and position data for rendering and updates and starts a chain that updates the descendants after
    void CalculateGlobalData() noexcept;

    size_t GetChildCount() const noexcept {return m_Children.size();}
    UI* GetParent() const noexcept{return m_Parent;}
    //Vec2<float>& GetPosition() const noexcept {return (Vec2<float>&)m_Position;}
    UDim2<float, int16_t>& GetPosition() const noexcept {return (UDim2<float, int16_t>&)m_Position;}
    UDim2<float, int16_t>& GetSize() const noexcept {return (UDim2<float, int16_t>&)m_Size;}
    UIType GetUIType() const noexcept{return m_UIType;}

    Vec2<float>& GetGlobalSize() const noexcept{return (Vec2<float>&)m_GlobalSize;}
    Vec2<float>& GetGlobalPosition() const noexcept{return (Vec2<float>&)m_GlobalPosition;}

    const std::vector<UI*>& GetChildren() const noexcept{ return m_Children;}
public:
    ScreenSizeRestraint m_SizeRestraint;
    int8_t m_ZIndex = 0;
    bool m_Visible = true;
protected:
    void CallChildrenWindowResizeEvent(int width, int height);
protected:
    UIType m_UIType = UIType::UT_None;
    UI* m_Parent = nullptr;
    Gui* m_Gui = nullptr;
    std::vector<UI*> m_Children;
protected:
    UDim2<float, int16_t> m_Position;
    UDim2<float, int16_t> m_Size;

    //Gets calculated every frame
    Vec2<float> m_GlobalPosition;
    Vec2<float> m_GlobalSize;
};