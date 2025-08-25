project "Engine"
	kind "StaticLib"
	pchheader "ghepch.h"
	pchsource "src/ghepch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.ixx"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UI"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["angelscript"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"UI"
	}
	
	filter "configurations:Debug"
		links {
			library["angelscript_Debug"]
		}

	filter "configurations:Release"
		links {
			library["angelscript_Release"]
		}
