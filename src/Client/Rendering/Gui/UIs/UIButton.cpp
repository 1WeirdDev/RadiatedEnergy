#include "pch.h"
#include "UIButton.h"
#include "../Gui.h"

UIButton::UIButton(class Gui* gui) : UI(gui){
    m_UIType = UIType::Button;
    m_Gui->AddButtonReference(this);
}
UIButton::~UIButton(){
    m_Gui->RemoveButtonReference(this);
}
MouseButtonCallback* UIButton::AddMouseButtonCallback(MouseButtonCallback callback){
    m_MouseButtonCallbacks.push_back(callback);
    return &callback;
}