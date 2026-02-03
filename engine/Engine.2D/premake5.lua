project "Engine.2D"
	kind "StaticLib"
	pchheader "ghe2dpch.h"
	pchsource "src/ghe2dpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine"
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
		includeDir["Box2D"]
	}

	links {
		"Core",
		"Engine"
	}
	
	filter "configurations:Debug"
		links {
			library["Box2D_Debug"]
		}

	filter "configurations:Release"
		links {
			library["Box2D_Release"]
		}
