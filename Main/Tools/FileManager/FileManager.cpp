#include "FileManager.h"

//For our GLFWwindow
#include "GLFW/glfw3.h"

//Includes for File Manager
using namespace std;

void FileManager::DragNOpenStatic(GLFWwindow* window, int count, const char** paths)
{
    FileManager* wind = reinterpret_cast<FileManager*>(glfwGetWindowUserPointer(window));
    wind->DragNOpen(window, count, paths);
}

void FileManager::DragNOpen(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0; i < count; i++)
    {
        std::string str(paths[i]);
        FileList.push_back(str);
    }

    SingleFile = FileList[0];
    m_bFileLoaded = true;
}

FileManager::FileManager(GLFWwindow* ImguiWindow)
{
    //Drag and drop call back
    glfwSetWindowUserPointer(ImguiWindow, this);
    glfwSetDropCallback(ImguiWindow, DragNOpenStatic);

    m_bFileLoaded = false;
}

void FileManager::OpenDialog()
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";

    if (GetOpenFileName(&ofn))
        SingleFile = fileName;

    m_bFileLoaded = true;
}

string FileManager::ReadDirect(const string& filename)
{
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    stringstream file_stream;
    try {
        file.open(filename.c_str());
        file_stream << file.rdbuf();
        file.close();
    }
    catch (ifstream::failure e) {
        cout << "Error reading Shader File!" << endl;
    }
    return file_stream.str();
}

std::stringstream FileManager::GetFileBuffer()
{
    ifstream in(SingleFile, std::ios_base::in | std::ios_base::binary);

    stringstream buffer;
    buffer << in.rdbuf();

    in.close();

    return buffer;
}

bool FileManager::isThereAFile()
{
    return m_bFileLoaded;
}

void FileManager::setFileLoaded(bool b)
{
    m_bFileLoaded = false;
}

