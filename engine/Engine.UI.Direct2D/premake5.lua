project "Engine.UI.Direct2D"
	kind "StaticLib"
	pchheader "ghuid2dpch.h"
	pchsource "src/ghuid2dpch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.Core.DirectX",
		"Engine.UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["Engine.Core.DirectX"],
		includeDir["Engine.UI"],
		includeDir["tinyxml2"],
		includeDir["DirectX"]
	}
