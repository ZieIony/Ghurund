project "Engine.3D"
	kind "StaticLib"
	pchheader "ghe3dpch.h"
	pchsource "src/ghe3dpch.cpp"
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
		includeDir["Engine"]
	}

	links {
		"Core",
		"Engine"
	}
