project "UnitTest.Core"
	kind "SharedLib"
	pchheader "utcpch.h"
	pchsource "src/utcpch.cpp"
	staticruntime "on"

	dependson {
		"Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"]
	}

	links {
		"Core"
	}
