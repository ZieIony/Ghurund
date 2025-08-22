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
		"UnitTest.Core"
	}

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
		includeDir["UnitTest.Core"],
		includeDir["CRC"],
		includeDir["DirectX"],
		includeDir["GLEW"],
		includeDir["GLFW"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.OpenGL"
	}
