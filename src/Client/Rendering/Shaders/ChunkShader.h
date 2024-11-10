#pragma once

#include "../Shader.h"

class ChunkShader : public Shader{
public:
    ChunkShader(){}
    ~ChunkShader(){}
    //just default constructor all variables are on stack

    void Create();

    void LoadProjectionMatrix(float* data) const noexcept;
    void LoadViewMatrix(float* data) const noexcept;
    void LoadTransformationMatrix(float* data) const noexcept;
    void LoadPosition(float x, float y) const noexcept;

    void LoadColor(int index, float x, float y, float z) const noexcept;
private:
    GLint m_ProjMatrixLocation = -1;
    GLint m_ViewMatrixLocation = -1;
    GLint m_TransformationMatrixLocation = -1;
    GLint m_PositionLocation = -1;
};