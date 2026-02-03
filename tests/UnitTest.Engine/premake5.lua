project "UnitTest.Engine"
	kind "SharedLib"
	pchheader "utepch.h"
	pchsource "src/utepch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.2D",
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
		includeDir["Engine.2D"],
		includeDir["Engine.DirectX"],
		includeDir["Engine.OpenGL"],
		includeDir["UnitTest.Utils"],
		includeDir["CRC"],
		includeDir["DirectX"],
		includeDir["GLEW"],
		includeDir["GLFW"],
		includeDir["Box2D"]
	}

	links {
		"Core",
		"UnitTest.Utils",
		"Engine",
		"Engine.2D",
		"Engine.DirectX",
		"Engine.OpenGL"
	}
		
	filter "configurations:Debug"
		links {
			library["Box2D_Debug"]
		}

	filter "configurations:Release"
		links {
			library["Box2D_Release"]
		}
