#pragma once
#include "../../Libraries/IMGui/imgui.h"
#include "../../Libraries/IMGui/imgui_impl_glfw.h"
#include "../../Libraries/IMGui/imgui_impl_opengl3.h"
#include <cstdio>

#include <GL/gl3w.h>
// Include glfw3.h after our OpenGL definitions
<<<<<<< HEAD
=======
#include <string>
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed
#include <GLFW/glfw3.h>


class ImguiOpenGL
{
    GLFWwindow* window;

public:
<<<<<<< HEAD
    ImguiOpenGL();
=======
    ImguiOpenGL(const std::string& programName);
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed

    void SetupImGuiFrame();
    void RenderImGui();
    void CleanupImGuiGL();

    GLFWwindow* GetWindow() const;
};
