project "UI.OpenGL"
	kind "StaticLib"
	pchheader "ghuioglpch.h"
	pchsource "src/ghuioglpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"Engine.OpenGL"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UI"],
		includeDir["Engine.OpenGL"],
		includeDir["tinyxml2"]
	}
