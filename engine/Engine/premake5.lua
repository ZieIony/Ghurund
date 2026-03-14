project "Engine"
	kind "StaticLib"
	pchheader "ghepch.h"
	pchsource "src/ghepch.cpp"
	staticruntime "on"

	dependson {
		"Core"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.ixx"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core"
	}
