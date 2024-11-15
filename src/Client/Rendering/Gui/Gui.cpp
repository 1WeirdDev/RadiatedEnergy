#include "pch.h"
#include "Gui.h"

#include "UIDisplayManager.h"
#include "Input/Mouse.h"
Gui::Gui(){}
Gui::~Gui(){CleanUp();}

void Gui::CleanUp(){
    for(size_t i = 0; i < m_Children.size(); i++){
        m_Children[i]->DeleteChildren();
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

void Gui::AddButtonReference(UIButton* button){
    m_Buttons.push_back(button);
}

void Gui::RemoveButtonReference(UIButton* button){
    for(size_t i = 0; i < m_Buttons.size(); i++){
        if(m_Buttons[i] == button){
            m_Buttons.erase(m_Buttons.begin() + i);
            return;
        }
    }
}

bool Gui::OnMouseButtonEvent(int button, bool isDown){
    for(size_t i = 0; i < m_Buttons.size(); i++){
        float mouseX = Mouse::GetNormalizedMouseX();
        float mouseY = Mouse::GetNormalizedMouseY();

        Vec2<float> pos = m_Buttons[i]->GetGlobalPosition();
        Vec2<float> scale = m_Buttons[i]->GetGlobalSize();
        
        if(mouseX < pos.m_X || mouseX >= pos.m_X + scale.m_X || mouseY < pos.m_Y || mouseY >= pos.m_Y + scale.m_Y)continue;

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