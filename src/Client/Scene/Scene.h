#pragma once

#include "pch.h"

class Scene{
public:
    Scene();
    ~Scene();

    virtual void Init();
    virtual void CleanUp();
    virtual void Update();
    virtual void Draw();
public:

private:

};