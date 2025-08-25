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
		includeDir["GLFW"]
	}

	links {
		"Engine",
		"Core",
		library["GLEW"],
		library["GLFW"],
		"opengl32"
	}
	