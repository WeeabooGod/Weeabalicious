------------------------------------------------ Solution
workspace "Weeabalicious"
    configurations  { "Debug", "Release" }
    location        "Weeabalicious"
    startproject    "Weeabalicious"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

------------------------------------------------ Weeabalicious Project 
project "Weeabalicious"
    location    "Weeabalicious"
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
    location    "Weeabalicious/Libraries"
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