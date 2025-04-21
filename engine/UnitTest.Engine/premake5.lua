project "UnitTest.Engine"
	kind "SharedLib"
	pchheader "utepch.h"
	pchsource "src/utepch.cpp"
	staticruntime "on"

	dependson {
		"Engine",
		"Engine.DirectX",
		"Core",
		"UnitTest.Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["UnitTest.Core"],
		includeDir["Engine"],
		includeDir["Engine.DirectX"],
		includeDir["Core"],
		includeDir["CRC"],
		includeDir["DirectX"]
	}

	links {
		"Engine",
		"Engine.DirectX",
		"Core"
	}
