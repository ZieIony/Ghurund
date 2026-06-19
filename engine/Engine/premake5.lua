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
		includeDir["DirectX"],
		includeDir["assimp"]
	}

	links {
		"Core"
	}
	
	filter "configurations:Debug"
		links {
			library["assimp_Debug"],
			library["pugixml_Debug"],
			library["poly2tri_Debug"],
			library["kubazip_Debug"],
			library["minizip_Debug"],
			library["polyclipping_Debug"],
			library["zlib_Debug"]
		}

	filter "configurations:Release"
		links {
			library["assimp_Release"],
			library["pugixml_Release"],
			library["poly2tri_Release"],
			library["kubazip_Release"],
			library["minizip_Release"],
			library["polyclipping_Release"],
			library["zlib_Release"]
		}
