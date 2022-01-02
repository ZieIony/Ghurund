project "UnitTest.UI"
	kind "SharedLib"
	pchheader "pch.h"
	pchsource "src/pch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["Engine.UI"],
		includeDir["tinyxml2"]
	}

	links {
		"Engine.Core",
		"Engine.UI"
	}
		
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
