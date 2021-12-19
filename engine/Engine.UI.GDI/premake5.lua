project "Engine.UI.GDI"
	kind "StaticLib"
	pchheader "ghuigdipch.h"
	pchsource "src/ghuigdipch.cpp"
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
