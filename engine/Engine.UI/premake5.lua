project "Engine.UI"
	kind "StaticLib"
	pchheader "ghuipch.h"
	pchsource "src/ghuipch.cpp"
	staticruntime "on"

	dependson { "Engine.Core" }

	files {
		"src/**.h",
		"src/**.cpp",
		"generated/bindings/**.h"
	}

	includedirs {
		includeDir["Engine.UI"],
		includeDir["Engine.UI_bindings"],
		includeDir["Engine.Core"],
		includeDir["tinyxml2"]
	}
