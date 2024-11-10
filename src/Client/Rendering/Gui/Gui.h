#pragma once

#include "UI.h"
#include "UIs/Button.h"

class Gui{
public:
    Gui();
    ~Gui();

    void CleanUp();
    void Draw() const;

    /// @brief Creates a new instance of a ui and adds it as a child
    /// @tparam UIType A type that derives from base class UI 
    /// @return returns the newly created instance of ui
    template <typename UIType, typename ...Arg>
    UIType* CreateChild(Arg... args){
        UIType* ui = new UIType(this, args...);
        ui->m_Gui = this;
        m_Children.push_back(ui);

        if(ui->m_UIType == UT_Button)
            m_Buttons.push_back((Button*)ui);

        return ui;
    }

    void AddButtonReference(Button* button);
    void RemoveButtonReference(Button* button);

    bool OnMouseButtonEvent(int button, bool isDown);
    void OnWindowResizeEvent(int width, int height);
private:
    //Can be touched by friend class Button
private:
    std::vector<UI*> m_Children;
    std::vector<Button*> m_Buttons;
};