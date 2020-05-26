#include "../../Libraries/IMGui/imgui.h"
#include "../../Libraries/IMGui/imgui_internal.h"

<<<<<<< HEAD
bool firstTime = true;

=======
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed
inline void SetupDockspace()
{
    //Dockspace
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
<<<<<<< HEAD
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    dockspace_flags |= ImGuiDockNodeFlags_NoWindowMenuButton;
    dockspace_flags |= ImGuiDockNodeFlags_NoCloseButton;
=======
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
<<<<<<< HEAD
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
=======
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed
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
<<<<<<< HEAD
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
=======
    ImGui::Begin("DockSpace", nullptr, window_flags);
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

<<<<<<< HEAD
    ImGuiID dockspace_id = ImGui::GetID("DockSpace");

    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    if (firstTime)
    {
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID DockLeft = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.15f, nullptr, &dock_main_id);
        ImGuiID DockBottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.30f, nullptr, &dock_main_id);
        ImGuiID DockUp = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.20, nullptr, &dock_main_id);
        ImGuiID DockRight = ImGui::DockBuilderSplitNode(DockBottom, ImGuiDir_Right, 0.15f, NULL, &DockBottom);

        ImGui::DockBuilderDockWindow("Window", DockLeft);
        ImGui::DockBuilderDockWindow("Memory Viewer", DockBottom);
        ImGui::DockBuilderDockWindow("Memory List", DockRight);
        ImGui::DockBuilderDockWindow("Viewport", DockUp);
        ImGui::DockBuilderFinish(dockspace_id);

        firstTime = false;  
    }

=======
    ImGuiID DockspaceID = ImGui::GetID("DockSpace");

    if (!ImGui::DockBuilderGetNode(DockspaceID))
    {
        ImGui::DockBuilderRemoveNode(DockspaceID); // Clear out existing layout
        ImGui::DockBuilderAddNode(DockspaceID, dockspace_flags); // Add empty node
        ImGui::DockBuilderSetNodeSize(DockspaceID, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = DockspaceID; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID DockLeft = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.75f, nullptr, &dock_main_id);
        ImGuiID DockRight = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.15f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow("Game Search", DockLeft);
        ImGui::DockBuilderDockWindow("Profiles", DockRight);


        // Disable tab bar for custom toolbar so that it remains docked.
        ImGuiDockNode* node = ImGui::DockBuilderGetNode(DockLeft);
        node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        node = ImGui::DockBuilderGetNode(DockRight);
        node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

    	//Finish that shit
        ImGui::DockBuilderFinish(DockspaceID);
    }

	//We done bois
    ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), dockspace_flags);
>>>>>>> 40fc11046fb06e8267e48fbc2506a4228f75a8ed
}

inline void EndDockspace()
{
    ImGui::End();
}
