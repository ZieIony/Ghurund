project "UI.OpenGL"
	kind "StaticLib"
	pchheader "ghuioglpch.h"
	pchsource "src/ghuioglpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.OpenGL",
		"UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.OpenGL"],
		includeDir["UI"],
		includeDir["GLEW"],
		includeDir["GLFW"]
	}
	
	links {
		"Core",
		"Engine",
		"Engine.OpenGL",
		"UI",
		library["GLEW"],
		library["GLFW"],
		"opengl32"
	}