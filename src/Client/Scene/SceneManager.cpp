#include "pch.h"
#include "SceneManager.h"

std::vector<Scene*> SceneManager::m_Scenes;
void SceneManager::Init(){
    //Useless code
    m_Scenes.resize(0);
}
void SceneManager::Shutdown(){
    for(size_t i = 0; i < m_Scenes.size(); i++){
        m_Scenes[i]->CleanUp();
        delete m_Scenes[i];
    }
    m_Scenes.resize(0);
}
void SceneManager::Update(){
    for(size_t i = 0; i < m_Scenes.size(); i++)
        m_Scenes[i]->Update();
}
void SceneManager::Draw(){
    for(size_t i = 0; i < m_Scenes.size(); i++)
        m_Scenes[i]->Draw();
}

bool SceneManager::RemoveScene(Scene* scene){
    for(size_t i = 0; i < m_Scenes.size(); i++){
        if(m_Scenes[i] == scene){
            m_Scenes.erase(m_Scenes.begin() + i);
            return true;
        }
    }
    return false;
}