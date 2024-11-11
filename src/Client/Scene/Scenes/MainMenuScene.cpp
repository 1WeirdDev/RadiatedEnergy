#include "pch.h"
#include "MainMenuScene.h"
#include "Core/Logger.h"
#include "Rendering/Gui/UIs/Frame.h"

MainMenuScene::MainMenuScene(){

}
void MainMenuScene::Init(){
    Frame* frame = m_Gui.CreateChild<Frame>();
    frame->SetSize(0.5f, 0.5f, 0, 0);
}
void MainMenuScene::CleanUp(){
    m_Gui.CleanUp();
}
void MainMenuScene::Update(){
}
void MainMenuScene::Draw(){
    m_Gui.Draw();
}
void MainMenuScene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){
    
}