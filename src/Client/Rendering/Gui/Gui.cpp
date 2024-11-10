#include "pch.h"
#include "Gui.h"

#include "UIDisplayManager.h"
#include "Input/Input.h"

Gui::Gui(){}
Gui::~Gui(){CleanUp();}

void Gui::CleanUp(){
    for(size_t i = 0; i < m_Children.size(); i++){
        delete m_Children[i];
    }
    m_Children.resize(0);
    m_Buttons.resize(0);
}

void Gui::Draw() const{
    for(size_t i = 0; i < m_Children.size(); i++){
        UIDisplayManager::DrawUI(m_Children[i], 0);
    }
}

void Gui::AddButtonReference(Button* button){
    m_Buttons.push_back(button);
}

void Gui::RemoveButtonReference(Button* button){
    for(size_t i = 0; i < m_Buttons.size(); i++){
        if(m_Buttons[i] == button){
            m_Buttons.erase(m_Buttons.begin() + i);
            return;
        }
    }
}

bool Gui::OnMouseButtonEvent(int button, bool isDown){
    for(size_t i = 0; i < m_Buttons.size(); i++){
        float mouseX = Input::GetMouseNormalizedX();
        float mouseY = Input::GetMouseNormalizedY();

        Vec2<float> pos = m_Buttons[i]->GetGlobalPosition();
        Vec2<float> scale = m_Buttons[i]->GetGlobalSize();
        
        if(mouseX < pos.x || mouseX >= pos.x + scale.x || mouseY < pos.y || mouseY >= pos.y + scale.y)continue;

        const std::vector<MouseButtonCallback>& callbacks = m_Buttons[i]->GetMouseButtonCallbacks();
        for(size_t j = 0; j < callbacks.size(); j++){
            if(callbacks[j](button, isDown))
                return false;
        }
    }

    //TODO: sort
    return false;
}
void Gui::OnWindowResizeEvent(int width, int height){
    for(size_t i = 0; i < m_Children.size(); i++){
        m_Children[i]->CalculateGlobalData();

        //TODO MAYBE: instead of a whole window resize event manually check if its a textlable or textbox and update it
        m_Children[i]->OnWindowResizeEvent(width, height);
        m_Children[i]->CallChildrenWindowResizeEvent(width, height);
    }
}