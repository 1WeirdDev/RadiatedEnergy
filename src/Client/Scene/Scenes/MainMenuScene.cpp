#include "pch.h"
#include "MainMenuScene.h"
#include "Core/Logger.h"
#include "Core/Time.h"
#include "Rendering/Gui/UIs/UIFrame.h"
#include "Rendering/Gui/UIDisplayManager.h"

MainMenuScene::MainMenuScene(){

}
void MainMenuScene::Init(){
    UIFrame* frame = m_Gui.CreateChild<UIFrame>();
    frame->SetSize(0.5f, 0.5f, 0, 0);

    m_Label = frame->CreateChild<UITextLabel>(UIDisplayManager::GetFont("RobotoRegular"));
    Font* font = UIDisplayManager::GetFont("RobotoRegular");
    m_Label->SetFont(font);
    m_Label->SetText("WORLD");
    m_Label->SetPosition(0, 1, 0, -font->GetFontSize());
    m_Label->SetSize(1.0f, 0, 0, font->GetFontSize());
}
void MainMenuScene::CleanUp(){
    m_Gui.CleanUp();
}
void MainMenuScene::Update(){
    m_Label->SetText(std::to_string((int)(1.0 / Time::GetDeltaTime())).c_str());
}
void MainMenuScene::Draw(){
    m_Gui.Draw();
}
void MainMenuScene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){
    
}