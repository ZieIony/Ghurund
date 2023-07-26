project "UnitTest"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
	staticruntime "on"

	dependson {
		"Engine",
		"Engine.Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine"],
		includeDir["Engine.Core"],
		includeDir["CRC"]
	}

	links {
		"Engine",
		"Engine.Core"
	}
