#pragma once

#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class FileManager
{
    struct GLFWwindow* window;

    //Keep track of a single + FileList
    std::string SingleFile;
    std::vector<std::string> FileList;

    bool m_bFileLoaded;

public:
    FileManager(struct GLFWwindow* window);

    static void DragNOpenStatic(GLFWwindow* window, int count, const char** paths);
    void DragNOpen(GLFWwindow* window, int count, const char** paths);
    void OpenDialog();

    static std::string ReadDirect(const std::string& filename);
    std::stringstream GetFileBuffer();

    bool isThereAFile();
    void setFileLoaded(bool b);
};
