#include "pch.h"

#include "Shader.h"
#include "Core.h"
#include "Core/Logger.h"

Shader::Shader(){

}
Shader::~Shader(){

}

void Shader::CleanUp(){
    if(!m_IsCreated)return;
    glDeleteShader(m_VertexShaderId);
    glDeleteShader(m_FragmentShaderId);
    glDeleteProgram(m_ProgramId);
    m_VertexShaderId = 0;
    m_FragmentShaderId = 0;
    m_ProgramId = 0;
    m_IsCreated = false;
}
void Shader::Start() const noexcept{
    glUseProgram(m_ProgramId);
}
void Shader::Stop(){
    glUseProgram(0);
}
GLint Shader::LoadShader(const char* shaderData, int shaderType){
    GLint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderData, nullptr);
    glCompileShader(shader);
    
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        CORE_ERROR("Failed to create shader");
        
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		char* data = new char[maxLength + 1];
		data[maxLength] = 0;

		for (unsigned short i = 0; i < maxLength; i++)data[i] = errorLog[i];
		CORE_ERROR(data);

        glDeleteShader(shader);
        glfwTerminate();
        MESSAGE_BOX("Shader Error", "Failed to compile Shader");
        std::exit(-1);
    }
    return shader;
}

void Shader::CreateWithSource(const char* vertexShaderData, const char* fragmentShaderData){
    m_VertexShaderId = LoadShader(vertexShaderData, GL_VERTEX_SHADER);
    m_FragmentShaderId = LoadShader(fragmentShaderData, GL_FRAGMENT_SHADER);
    m_ProgramId = glCreateProgram();

    glAttachShader(m_ProgramId, m_VertexShaderId);
    glAttachShader(m_ProgramId, m_FragmentShaderId);

    GLint success;
    glLinkProgram(m_ProgramId);
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        CORE_ERROR("Failed to link shader");
        
		GLint maxLength = 0;
		glGetShaderiv(m_ProgramId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_ProgramId, maxLength, &maxLength, &errorLog[0]);

		char* data = new char[maxLength + 1];
		data[maxLength] = 0;

		for (unsigned short i = 0; i < maxLength; i++)data[i] = errorLog[i];
		CORE_ERROR(data);
    }
    glValidateProgram(m_ProgramId);

    glDetachShader(m_ProgramId, m_VertexShaderId);
    glDetachShader(m_ProgramId, m_FragmentShaderId);
    m_IsCreated = true;
}

void Shader::BindAttribute(GLint index, const char* name) const{
    glBindAttribLocation(m_ProgramId, index, name);
}

GLint Shader::GetUniformLocation(const char* name) const{
    return glGetUniformLocation(m_ProgramId, name);
}

GLint Shader::GetBlockIndex(const char* name) const{
    return glGetUniformBlockIndex(m_ProgramId, name);
}
void Shader::LoadMat4x4(GLint location, float* value) noexcept{
    glUniformMatrix4fv(location, 1, false, value);
}

void Shader::LoadUInt(GLint location, GLuint value) noexcept{
    glUniform1ui(location, value);
}
void Shader::LoadInt(GLint location, GLint value) noexcept{
    glUniform1i(location, value);
}

void Shader::LoadFloat(GLint location, float value) noexcept{
    glUniform1f(location, value);
}
void Shader::LoadVector2(GLint location, float x, float y) noexcept{
    glUniform2f(location, x, y);
}
void Shader::LoadVector3(GLint location, float x, float y, float z) noexcept{
    glUniform3f(location, x, y, z);
}

void Shader::LoadVector3(GLint location, const Vec3<float>& vector) noexcept{
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::LoadIVector2(GLint location, GLint x, GLint y) noexcept{
    glUniform2i(location, x, y);
}
void Shader::LoadIVector3(GLint location, GLint x, GLint y, GLint z) noexcept{
    glUniform3i(location, x, y, z);
}