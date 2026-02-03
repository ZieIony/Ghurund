project "Engine.DirectX"
	kind "StaticLib"
	pchheader "ghedxpch.h"
	pchsource "src/ghedxpch.cpp"
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
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine"
	}
	