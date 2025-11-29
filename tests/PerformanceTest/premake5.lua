project "PerformanceTest"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"Engine"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UI"],
		includeDir["Engine"]
	}

	links {
		"Core",
		"UI",
		"Engine"
	}
