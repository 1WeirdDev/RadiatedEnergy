#pragma once

#include "pch.h"
#include "Math/Vec3.h"

class Shader{
public:
    Shader();
    virtual ~Shader();

    void CleanUp();
    void Start() const noexcept;
    static void Stop();

    void CreateWithSource(const char* vertexShaderData, const char* fragmentShaderData);

    static GLint LoadShader(const char* shaderData, int shaderType);

    void BindAttribute(GLint index, const char* name) const;
    GLint GetUniformLocation(const char* name) const;
    GLint GetBlockIndex(const char* name) const;
public:
    GLint GetProgramId() const {return m_ProgramId;}
    GLint GetVertexShaderId() const {return m_VertexShaderId;}
    GLint GetFragmetnShaderId() const {return m_FragmentShaderId;}
    bool IsCreated() const {return m_IsCreated;}
public:
    static void LoadUInt(GLint location, GLuint value) noexcept;
    static void LoadInt(GLint location, GLint value) noexcept;
    static void LoadFloat(GLint location, float value) noexcept;
    static void LoadIVector2(GLint location, GLint x, GLint y) noexcept;
    static void LoadIVector3(GLint location, GLint x, GLint y, GLint z) noexcept;
    static void LoadVector2(GLint location, float x, float y) noexcept;
    static void LoadVector3(GLint location, float x, float y, float z) noexcept;
    static void LoadVector3(GLint location, const Vec3<float>& vector) noexcept;
    static void LoadMat4x4(GLint location, float* value) noexcept;
protected:
    GLint m_ProgramId = 0;
    GLint m_VertexShaderId = 0;
    GLint m_FragmentShaderId = 0;
    bool m_IsCreated = false;
};