#include "../Libraries/IMGui/imgui.h"
#include "../Libraries/IMGui/imgui_impl_glfw.h"
#include "../Libraries/IMGui/imgui_impl_opengl3.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

//Misc Tools
#include "Tools/imgui_memory_editor.h"
#include "Tools/file_manager.h"
#include "Rendering/opengl_shader.h"

#include <GL/gl3w.h>
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include <shellapi.h>


#define PI 3.14159265358979323846
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
void create_triangle(unsigned int& vbo, unsigned int& vao, unsigned int& ebo)
{
    // create the triangle
    float triangle_vertices[] = {
        0.0f, 0.25f, 0.0f,	// position vertex 1
        1.0f, 0.0f, 0.0f,	 // color vertex 1
        0.25f, -0.25f, 0.0f,  // position vertex 1
        0.0f, 1.0f, 0.0f,	 // color vertex 1
        -0.25f, -0.25f, 0.0f, // position vertex 1
        0.0f, 0.0f, 1.0f,	 // color vertex 1
    };
    unsigned int triangle_indices[] = {
        0, 1, 2 };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DragNDrop(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0; i < count; i++)
    {
        //TODO handle dragNDrops Here
    }
}

//Main program
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Weeabalicious", NULL, NULL);
    if (window == NULL) { return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    bool err = gl3wInit() != 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiCol_DragDropTarget;
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);

    // create our geometries
    unsigned int vbo, vao, ebo;
    create_triangle(vbo, vao, ebo);

    //Init Shader
    Shader triangle_shader;
    triangle_shader.init(FileManager::read("Rendering/Shaders/simple-shader.vs"), FileManager::read("Rendering/Shaders/simple-shader.fs"));

    //Drag and drop call back
    glfwSetDropCallback(window, DragNDrop);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Process Window Events
        MSG msg;

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glfwPollEvents();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Do Things

        //Dockspace
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        //Menu Bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Docking"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        //Memory Editor
        static unsigned char ram[0x1000] = { 0 };
        if ((ImGui::GetFrameCount() % 60) == 0)
            for (int n = 0; n < 0x1000; n++)
                ram[n] = ((n % 16) << 4) | ((ram[n] + 1) & 0x0F);

        static MemoryEditor MemEdit;
        ImGui::Begin("Memory Viewer");
        MemEdit.DrawContents(ram, sizeof(ram), (size_t)ram);
        MemEdit.OptShowOptions = false;
        ImGui::End();

        //Show Demo Window
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // rendering our geometries
        triangle_shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // render your GUI
        ImGui::Begin("Triangle Position/Color");
        static float rotation = 0.0;
        ImGui::SliderFloat("rotation", &rotation, 0, 2 * PI);
        static float translation[] = { 0.0, 0.0 };
        ImGui::SliderFloat2("position", translation, -1.0, 1.0);
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        // pass the parameters to the shader
        triangle_shader.setUniform("rotation", rotation);
        triangle_shader.setUniform("translation", translation[0], translation[1]);
        // color picker
        ImGui::ColorEdit3("color", color);
        // multiply triangle's color with this color
        triangle_shader.setUniform("color", color[0], color[1], color[2]);
        ImGui::End();

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();


        ImGui::End();

        //Finish Doing things and render to Screen
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
  
}