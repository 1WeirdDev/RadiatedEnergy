#pragma once

#include "UI.h"
#include "UIs/UIButton.h"

class Gui{
public:
    Gui();
    ~Gui();

    void CleanUp();
    void Draw() const;

    /// @brief Creates a new instance of a ui that the gui owns and adds it to list
    /// @tparam UIType A type that derives from base class UI 
    /// @return returns the newly created instance of ui
    template <typename TYPE, typename ...Arg>
    TYPE* CreateChild(Arg&&... args){
        TYPE* ui = new TYPE(this, args...);
        ui->m_Gui = this;
        m_Children.push_back(ui);

        if(ui->m_UIType == UIType::Button)
            m_Buttons.push_back((UIButton*)ui);

        return ui;
    }

    void AddButtonReference(UIButton* button);
    void RemoveButtonReference(UIButton* button);

    bool OnMouseButtonEvent(int button, bool isDown);
    void OnWindowResizeEvent(int width, int height);
private:
    //Can be touched by friend class Button
private:
    std::vector<UI*> m_Children;
    std::vector<UIButton*> m_Buttons;
};