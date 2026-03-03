project "Engine.2D.DirectX"
	kind "StaticLib"
	pchheader "ghe2ddxpch.h"
	pchsource "src/ghe2ddxpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.2D"
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
		includeDir["Engine.DirectX"],
		includeDir["Engine.2D"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.2D"
	}
	