project "Engine.OpenGL"
	kind "StaticLib"
	pchheader "gheoglpch.h"
	pchsource "src/gheoglpch.cpp"
	staticruntime "on"

	dependson {
		"Engine",
		"Core"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.ixx"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["GLEW"],
		includeDir["GLFW"],
		includeDir["tinyxml2"]
	}

	links {
		"Engine",
		"Core",
		library["GLEW"],
		library["GLFW"],
		"opengl32"
	}
	
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
