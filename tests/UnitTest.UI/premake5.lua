project "UnitTest.UI"
	kind "SharedLib"
	pchheader "utuipch.h"
	pchsource "src/utuipch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"Engine",
		"UnitTest.Utils"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["UnitTest.Utils"],
		includeDir["Core"],
		includeDir["UI"],
		includeDir["DirectX"],
		includeDir["Engine"]
	}

	links {
		"Core",
		"UnitTest.Utils",
		"UI",
		"Engine"
	}
