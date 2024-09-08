project "PerformanceTest"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
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

	links {
		"Core",
		"UI"
	}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
