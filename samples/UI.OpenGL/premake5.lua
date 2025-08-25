project "Samples.UI.OpenGL"
	kind "WindowedApp"
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
