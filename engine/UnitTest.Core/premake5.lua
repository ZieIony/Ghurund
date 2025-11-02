project "UnitTest.Core"
	kind "SharedLib"
	pchheader "utcpch.h"
	pchsource "src/utcpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UnitTest.Utils"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UnitTest.Utils"]
	}

	links {
		"Core",
		"UnitTest.Utils"
	}
