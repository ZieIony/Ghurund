project "UnitTest.Engine"
	kind "SharedLib"
	pchheader "utepch.h"
	pchsource "src/utepch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
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
		includeDir["Engine.DirectX"],
		includeDir["Engine.OpenGL"],
		includeDir["UnitTest.Utils"],
		includeDir["CRC"],
		includeDir["DirectX"],
		includeDir["GLEW"],
		includeDir["GLFW"]
	}

	links {
		"Core",
		"UnitTest.Utils",
		"Engine",
		"Engine.DirectX",
		"Engine.OpenGL"
	}
