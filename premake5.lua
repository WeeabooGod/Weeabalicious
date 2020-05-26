------------------------------------------------ Solution
workspace "GreenlumaRebornManager"
    configurations  { "Debug", "Release" }
    location        "GreenlumaRebornManager"
    startproject    "GreenlumaRebornManager"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

------------------------------------------------ GreenlumaRebornManager Project 
project "GreenlumaRebornManager"
    location    "GreenlumaRebornManager"
    dependson   { "Libraries" }
    kind        "windowedapp"
    language    "C++"
	debugdir	"Main"

    includedirs {
		"Libraries/OpenGL/GLFW/include",
		"Libraries/OpenGL/GL/include",
    }
	
	libdirs {
		"Libraries/OpenGL/GLFW/lib-vc2019",
	}

    files {
        "Main/**.cpp",
		"Main/**.h",
		"Main/Tools/**",
		"Main/Config/**",
    }

    links {
		"Libraries",
        "opengl32",
		"glfw3",
    }
------------------------------------------------ Libraries Project
project "Libraries"
    location    "GreenlumaRebornManager/Libraries"
    kind        "StaticLib"
	language    "C++"
	
    includedirs {
		"Libraries/OpenGL/GLFW/include",
		"Libraries/OpenGL/GL/include",
    }
	
	libdirs {
		"Libraries/OpenGL/GLFW/lib-vc2019",
	}

    files {
        "Libraries/OpenGL/**",
        "Libraries/IMGui/**",
        "Libraries/cJSON/cJSON.c",
        "Libraries/cJSON/cJSON.h",
    }