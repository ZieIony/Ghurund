project "UnitTest.UI"
	kind "SharedLib"
	pchheader "utuipch.h"
	pchsource "src/utuipch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"Engine",
		"Engine.DirectX",
		"UnitTest.Utils"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.DirectX"],
		includeDir["UnitTest.Utils"],
		includeDir["UI"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"UI",
		"UnitTest.Utils"
	}
