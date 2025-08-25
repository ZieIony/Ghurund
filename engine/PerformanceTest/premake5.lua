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
		includeDir["UI"]
	}

	links {
		"Core",
		"UI"
	}
