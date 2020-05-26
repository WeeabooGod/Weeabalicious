#include "Startup/SetupImGuiGL.h"
#include "Startup/SetupDockspace.h"

//My Tools Tools
#include "Tools/imgui_memory_editor.h"
#include "Tools/FileManager/FileManager.h"

//Rendering
#include "Rendering/opengl_shader.h"



#define PI 3.14159265358979323846
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


//Main program
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //Setup the GL
    ImguiOpenGL Weebalicious;

    FileManager WeebFileManager(Weebalicious.GetWindow());

    // create our geometries
    unsigned int vbo, vao, ebo;
    create_triangle(vbo, vao, ebo);

    //Init Shader
    Shader triangle_shader;
    triangle_shader.init(FileManager::ReadDirect("Rendering/Shaders/simple-shader.vs"), FileManager::ReadDirect("Rendering/Shaders/simple-shader.fs"));

    std::stringstream buffer;
    std::string bufferStr;

    // Main loop
    while (!glfwWindowShouldClose(Weebalicious.GetWindow()))
    {
        //OpenGL Shit
        glfwPollEvents();
        glClearColor(0.27f, 0.27f, 0.27f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Is there any File Buffers?
        if (WeebFileManager.isThereAFile())
        {
            buffer = WeebFileManager.GetFileBuffer();
            bufferStr = buffer.str();
            WeebFileManager.setFileLoaded(false);
        }

        // Start the Dear ImGui frame
        Weebalicious.SetupImGuiFrame();

        //Dockspace
        SetupDockspace();

        //Menu Bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open File"))
                {
                    WeebFileManager.OpenDialog();
                }
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
        if (buffer)
            MemEdit.DrawContents((void*)bufferStr.c_str(), bufferStr.size(), (size_t)bufferStr.c_str());
        MemEdit.OptShowOptions = false;
        ImGui::End();

        //Show Demo Window
        ImGui::ShowDemoWindow();

        // rendering our geometries
        triangle_shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // render your GUI
        ImGui::Begin("Memory List");
        ImGui::Button("Hello!");
        ImGui::End();

        ImGui::Begin("Window");
        ImGui::Button("Hello!");
        ImGui::End();

        ImGui::Begin("Viewport");
        ImGui::End();


        //End Dockspace
        EndDockspace();

        //Finish Doing things and render to Screen
        Weebalicious.RenderImGui();
    }

    // Cleanup
    Weebalicious.CleanupImGuiGL();
    return 0;
  
}