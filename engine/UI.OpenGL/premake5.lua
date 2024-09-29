project "UI.OpenGL"
	kind "StaticLib"
	pchheader "ghuioglpch.h"
	pchsource "src/ghuioglpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UI"],
		includeDir["tinyxml2"]
	}
