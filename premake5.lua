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
    dependson   { "OpenGL Libraries" }
    kind        "WindowedApp"
    language    "C++"
	debugdir	"Weeabalicious"
	--pchheader	"GamePCH.h"
	--pchsource	"Game/Source/Base/WinMain.cpp"

    includedirs {
		"Libraries/OpenGL/GLFW/include",
		"Libraries/OpenGL/GL/include",
    }
	
	libdirs {
		"Libraries/OpenGL/GLFW/lib-vc2019"
	}

    files {
        "Main/**.cpp",
		"Main/**.h",
		"Main/Tools/**",
    }

    links {
		"OpenGL Libraries",
        "opengl32",
		"glfw3",
    }
------------------------------------------------ Libraries Project
project "OpenGL Libraries"
    location    "Weeabalicious/Libraries"
    kind        "StaticLib"
	language    "C++"
	
    includedirs {
		"Libraries/OpenGL/GLFW/include",
		"Libraries/OpenGL/GL/include",
    }
	
	libdirs {
		"Libraries/OpenGL/GLFW/lib-vc2019"
	}

    files {
        "Libraries/OpenGL/**",
        "Libraries/IMGui/**",
    }