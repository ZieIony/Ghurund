project "Engine.3D.DirectX"
	kind "StaticLib"
	pchheader "ghe3ddxpch.h"
	pchsource "src/ghe3ddxpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.3D"
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
		includeDir["Engine.3D"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.3D"
	}
	