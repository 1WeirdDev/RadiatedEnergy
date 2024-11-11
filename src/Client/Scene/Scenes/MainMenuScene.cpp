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

    m_Label->SetFont(UIDisplayManager::GetFont("RobotoRegular"));
    m_Label->SetText("WORLD");
    m_Label->SetPosition(0,1, 0, -100);
    m_Label->SetSize(0.2f, 0.1f, 0, 0);
}
void MainMenuScene::CleanUp(){
    m_Gui.CleanUp();
}
void MainMenuScene::Update(){
    m_Label->SetText(std::to_string(1.0 / Time::GetDeltaTime()).c_str());
}
void MainMenuScene::Draw(){
    m_Gui.Draw();
}
void MainMenuScene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){
    
}