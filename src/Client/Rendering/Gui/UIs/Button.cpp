#include "pch.h"
#include "Button.h"
#include "../Gui.h"

Button::Button(class Gui* gui) : UI(gui){
    m_UIType = UT_Button;
    m_Gui->AddButtonReference(this);
}
Button::~Button(){
    m_Gui->RemoveButtonReference(this);
    DeleteChildren();
}
MouseButtonCallback* Button::AddMouseButtonCallback(MouseButtonCallback callback){
    m_MouseButtonCallbacks.push_back(callback);
    return &callback;
}