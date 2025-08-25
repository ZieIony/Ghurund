project "UI.Direct2D"
	kind "StaticLib"
	pchheader "ghuid2dpch.h"
	pchsource "src/ghuid2dpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.DirectX",
		"UI"
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
		includeDir["UI"],
		includeDir["DirectX"]
	}
	
	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"UI"
	}
