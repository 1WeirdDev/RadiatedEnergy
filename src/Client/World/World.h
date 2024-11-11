#pragma once

class World{
public:
    World();
    ~World();

    void Init();
    void CleanUp();

    void Update();
    void Draw();
};