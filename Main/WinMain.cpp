#include "Startup/SetupImGuiGL.h"
#include "Startup/SetupDockspace.h"

//Pretty much a list of all headers will be in helpers
#include "Tools/Helpers.h"

#include <curl\curl.h>
#include <iostream>

using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//Main program
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Load our main directory where we will be getting data from
    string AppDataPath = InitDirectories();
    string ConfigPath = AppDataPath + "Config.json";

    ifstream file(ConfigPath);
    string FileContents;
	FileContents.assign(istreambuf_iterator<char>(file),istreambuf_iterator<char>());

	//Parse it as a Json file
    cJSON* jConfig = cJSON_Parse(FileContents.c_str());

	//A copy of our variables, which we will get from our config
    string ProgramName;
    string GreenlumaPath;
	
	//If our Json file is null we need to error handle
	if (!jConfig)
	{
        //TODO: Error handling
	}

	//fill our vairable references
    ProgramName = cJSON_GetObjectItem(jConfig, "ProgramName")->valuestring;
    GreenlumaPath = cJSON_GetObjectItem(jConfig, "GreenlumaPath")->valuestring;

	
    //Setup the GL
    ImguiOpenGL GLRManager(ProgramName);

    // Main loop
    while (!glfwWindowShouldClose(GLRManager.GetWindow()))
    {
        //OpenGL Shit
        glfwPollEvents();
        glClearColor(0.27f, 0.27f, 0.27f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Start the Dear ImGui frame
        GLRManager.SetupImGuiFrame();

    	//Ask for Path if there is no path
        if (GreenlumaPath.empty())
        {
            ImGui::OpenPopup("Find Greenluma Path");
        	
            if (ImGui::BeginPopupModal("Find Greenluma Path", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("There is no path assosiated for Greenluma, please locate your Greenluma path. (ie. Where your DLLInjector is)");
                ImGui::Separator();
                ImGui::Spacing();
            	
                static char pathInput[1024];
            	
                ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.7f);
                ImGui::InputText("", pathInput, IM_ARRAYSIZE(pathInput), ImGuiInputTextFlags_None); ImGui::SameLine();
            	if (ImGui::Button("Find Path"))
            	{
                    string filepath = BrowseForFolder();
                    strcpy_s(pathInput, filepath.c_str());
            	}

            	//We are done
                if (ImGui::Button("Done"))
                {
                    GreenlumaPath = pathInput;
                    replace(GreenlumaPath.begin(), GreenlumaPath.end(), '\\', '/');

                	//Only end if there is even a path
                	if (!GreenlumaPath.empty())
                	{
                		//Replace what we modified
                        cJSON_ReplaceItemInObject(jConfig, "GreenlumaPath", cJSON_CreateString(GreenlumaPath.c_str()));

                		//Write it to our Config in case our program crashes/closes prematurely
                        WriteToConfig(jConfig, ConfigPath);
                        ImGui::CloseCurrentPopup();
                	}
                }
            	
                ImGui::EndPopup();
            }
        }

        //Dockspace
        SetupDockspace();

        //Show Demo Window
        ImGui::ShowDemoWindow();

        // render your GUI
        ImGui::Begin("Profiles");
        ImGui::Button("Hello!");
        ImGui::End();

        ImGui::Begin("Game Search");
        ImGui::Button("Hello!");
        ImGui::End();


        //End Dockspace
        EndDockspace();

        //Testing
        CURL* curl;
        CURLcode res;
    	
        curl = curl_easy_init();

        string readbuffer;

        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://steamdb.info/search/?a=app&q=Monster+Hunter");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readbuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120);
            res = curl_easy_perform(curl);
        }
    	
        curl_easy_cleanup(curl);

        size_t found = readbuffer.find("class");
        size_t size = readbuffer.size();
    	
        //Finish Doing things and render to Screen
        GLRManager.RenderImGui();
    }

    // Cleanup
    GLRManager.CleanupImGuiGL();

	//Make sure we properly write all of our vairables back into our config.
    WriteToConfig(jConfig, ConfigPath);
	
    return 0;
}