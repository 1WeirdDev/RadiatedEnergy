#include "pch.h"
#include "Scene.h"

Scene::Scene(){}
Scene::~Scene(){
    
}

void Scene::Init(){}
void Scene::CleanUp(){}
void Scene::Update(){}
void Scene::Draw(){}
void Scene::LateDraw(){}
void Scene::HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key){}