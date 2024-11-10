#include "pch.h"
#include "Window.h"
#include "Core/Logger.h"

GLFWwindow* Window::s_Window = nullptr;
bool Window::s_ShouldBeOpen = false;

void Window::Create(){
    if(!glfwInit()){
        CORE_ERROR("Failed to initialize GLFW");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    s_Window = glfwCreateWindow(1280, 720, GAME_NAME, nullptr, nullptr);

    if(!s_Window){
        CORE_ERROR("Failed to create window");
        std::exit(-1);
    }

    glfwMakeContextCurrent(s_Window);

    if(glewInit() != GLEW_OK){
        CORE_ERROR("Failed to initialize glew");
        glfwTerminate();
        std::exit(-1);
    }

    glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window){
        s_ShouldBeOpen = false;
    });
    s_ShouldBeOpen = true;
    CORE_INFO("Created Window");
}
void Window::Shutdown(){
    glfwDestroyWindow(s_Window);
    glfwTerminate();
}

void Window::Update(){
    glfwSwapBuffers(s_Window);
    glfwPollEvents();
}