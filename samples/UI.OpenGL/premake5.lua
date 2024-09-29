project "Samples.UI.OpenGL"
	kind "ConsoleApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.OpenGL",
		"UI",
		"UI.OpenGL"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.OpenGL"],
		includeDir["UI"],
		includeDir["UI.OpenGL"],
		includeDir["tinyxml2"],
		includeDir["GLEW"],
		includeDir["GLFW"]
	}

	links {
		"Core",
		"Engine",
		"Engine.OpenGL",
		"UI",
		"UI.OpenGL",
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
