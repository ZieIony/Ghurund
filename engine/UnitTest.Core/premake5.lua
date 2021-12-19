project "UnitTest.Core"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"]
	}

	links {
		"Engine.Core"
	}
