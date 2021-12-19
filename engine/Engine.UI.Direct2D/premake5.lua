project "Engine.UI.Direct2D"
	kind "StaticLib"
	pchheader "ghuidxpch.h"
	pchsource "src/ghuidxpch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["Engine.UI"],
		includeDir["tinyxml2"]
	}
