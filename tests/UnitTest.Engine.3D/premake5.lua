project "UnitTest.Engine.3D"
	kind "SharedLib"
	pchheader "ute3dpch.h"
	pchsource "src/ute3dpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.3D",
		"Engine.DirectX",
		"Engine.OpenGL",
		"UnitTest.Utils"
	}

	defines { "RES_DIR=LR\"($(solutionDir)resources\\test)\"" }

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.3D"],
		includeDir["Engine.DirectX"],
		includeDir["Engine.OpenGL"],
		includeDir["UnitTest.Utils"],
		includeDir["DirectX"],
		includeDir["GLEW"],
		includeDir["GLFW"]
	}

	links {
		"Core",
		"Engine",
		"Engine.2D",
		"Engine.DirectX",
		"Engine.OpenGL",
		"UnitTest.Utils"
	}
