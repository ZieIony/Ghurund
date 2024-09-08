project "UnitTest.UI"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
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
		includeDir["tinyxml2"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"UI"
	}
		
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
