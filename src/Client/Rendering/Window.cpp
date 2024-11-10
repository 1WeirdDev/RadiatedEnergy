#include "pch.h"

#include "Core.h"
#include "Window.h"
#include "Core/Logger.h"
#include "Core/Time.h"
#include "Game.h"

WindowData Window::s_Data;
bool Window::s_ShouldUpdate;
float Window::s_AspectRatio = 1.0f;
float Window::s_InverseAspectRatio = 1.0f;
float Window::s_PixelSizeX = 0;
float Window::s_PixelSizeY = 0;

GLFWwindow* Window::s_Window = nullptr;


void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    if(severity != GL_DEBUG_SEVERITY_HIGH)return;
    CORE_DEBUG("GL ERROR {0}, {1}, {2}, {3}, ({4})", source, type, id, severity, message);
}
void Window::Create(){
    if(!glfwInit()){
        CORE_ERROR("Failed to initialize glfw");
        MESSAGE_BOX("GLFW API ERROR", "Failed to initialize glfw");
        std::exit(-1);
    }

    //Only not resizable because of resizing stopping events
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#ifndef DIST
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Cor
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    s_Window = glfwCreateWindow(s_Data.m_Width, s_Data.m_Height, GAME_NAME, nullptr, nullptr);
    s_AspectRatio = (float)s_Data.m_Width / (float)s_Data.m_Height;
    s_InverseAspectRatio = (float)s_Data.m_Height / (float)s_Data.m_Width;
    s_PixelSizeX = 1.0f / (float)s_Data.m_Width;
    s_PixelSizeY = 1.0f / (float)s_Data.m_Height;

    if(!s_Window){
        CORE_ERROR("Failed to create window\n");
        MESSAGE_BOX("GLFW API ERROR", "Failed to create window");
        std::exit(-1);
    }

    glfwMakeContextCurrent(s_Window);

    GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(glfwGetPrimaryMonitor());
    s_Data.m_X = (videoMode->width - s_Data.m_Width) / 2;
    s_Data.m_Y = (videoMode->height - s_Data.m_Height) / 2;
    glfwSetWindowPos(s_Window, s_Data.m_X, s_Data.m_Y);

    glViewport(0, 0, s_Data.m_Width, s_Data.m_Height);
    if(glewInit() != GLEW_OK){
        CORE_ERROR("Failed to initialize opengl context\n");
        MESSAGE_BOX("GLEW API ERROR", "Failed to initialize glew");
        glfwTerminate();
        std::exit(-1);
    }

    CORE_DEBUG("{0}", (const char*)glGetString(GL_VERSION));
    glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window){
        s_ShouldUpdate = false;
    });

    glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int width, int height){
        Window::s_Data.m_Width = width;
        Window::s_Data.m_Height = height;
        s_AspectRatio = (float)s_Data.m_Width / (float)s_Data.m_Height;
        s_InverseAspectRatio = (float)s_Data.m_Height / (float)s_Data.m_Width;
        s_PixelSizeX = 1.0f / (float)s_Data.m_Width;
        s_PixelSizeY = 1.0f / (float)s_Data.m_Height;
        glViewport(0, 0, width, height);
        Game::OnWindowResizeEvent(width, height);
    });

    glfwSetWindowPosCallback(s_Window, [](GLFWwindow* window, int xPos, int yPos){
        Window::s_Data.m_X = xPos;
        Window::s_Data.m_Y = yPos;
        Game::OnWindowPosCallback(xPos, yPos);
    });

    glfwSetWindowFocusCallback(s_Window, [](GLFWwindow* window, int focused){
        Game::OnWindowFocusCallback(focused);
    });

    glfwSetWindowPosCallback(s_Window, [](GLFWwindow*, int xPos, int yPos){
        Game::OnWindowPosCallback(xPos, yPos);
    });

    //FUCK FRAME BUFFER RESIZE EVENTS 
    glfwSetFramebufferSizeCallback(s_Window, [](GLFWwindow* window, int width, int height){
        Time::Update();
    });

#ifndef DIST
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorCallback, nullptr);
#endif

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

    glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef DIST
    glfwSwapInterval(1);
#else
    glfwSwapInterval(0);
#endif

    s_ShouldUpdate = true;
}
void Window::Destroy(){
    glfwDestroyWindow(s_Window);
    glfwTerminate();
}
bool Window::ShouldUpdate() noexcept{return s_ShouldUpdate;}
void Window::Close(){
    s_ShouldUpdate = false;
}
void Window::Update(){
    glfwSwapBuffers(s_Window);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::SetBackgroundColor(float r, float g, float b){
    glClearColor(r, g, b, 1.0f);
}