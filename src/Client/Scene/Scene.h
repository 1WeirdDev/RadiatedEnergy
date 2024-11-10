#pragma once

#include "Input/Keyboard.h"

class Scene{
public:
    Scene();
    ~Scene();

    virtual void Init();
    virtual void CleanUp();
    virtual void Update();
    virtual void Draw();

    virtual void HandleKeyEvent(bool& handled, KeyState state, uint8_t modifiers, uint16_t key);
public:

private:

};