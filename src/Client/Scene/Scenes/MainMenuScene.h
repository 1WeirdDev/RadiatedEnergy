#pragma once

#include "../Scene.h"

#include "Rendering/Gui/Gui.h"
#include "Rendering/Gui/UIs/UITextLabel.h"

class MainMenuScene: public Scene{
public:
    MainMenuScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;

    void HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key) override;
private:
    Gui m_Gui;
    UITextLabel* m_Label;
};