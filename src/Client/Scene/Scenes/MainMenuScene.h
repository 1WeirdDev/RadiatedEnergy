#pragma once

#include "../Scene.h"
class MainMenuScene: public Scene{
public:
    MainMenuScene();

    void Init() override;
    void CleanUp() override;
    void Update() override;
    void Draw() override;
};