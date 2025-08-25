project "UnitTest.UI"
	kind "SharedLib"
	pchheader "utuipch.h"
	pchsource "src/utuipch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"UnitTest.Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["UnitTest.Core"],
		includeDir["Core"],
		includeDir["UI"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"UI"
	}
