#include "pch.h"
#include "SceneManager.h"

std::vector<Scene*> SceneManager::s_Scenes;
void SceneManager::Init(){
    //Useless code
    s_Scenes.resize(0);
}
void SceneManager::Shutdown(){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->CleanUp();
        delete s_Scenes[i];
    }
    s_Scenes.resize(0);
}
void SceneManager::Update(){
    for(size_t i = 0; i < s_Scenes.size(); i++)
        s_Scenes[i]->Update();
}
void SceneManager::Draw(){
    for(size_t i = 0; i < s_Scenes.size(); i++)
        s_Scenes[i]->Draw();
}

bool SceneManager::RemoveScene(Scene* scene){
    for(size_t i = 0; i < s_Scenes.size(); i++){
        if(s_Scenes[i] == scene){
            s_Scenes.erase(s_Scenes.begin() + i);
            return true;
        }
    }
    return false;
}

void SceneManager::HandleKeyEvent(KeyState state, uint8_t modifiers, uint16_t key){
    bool handled = false;
    for(size_t i = 0; i < s_Scenes.size(); i++){
        s_Scenes[i]->HandleKeyEvent(handled, state, modifiers, key);
    }
}