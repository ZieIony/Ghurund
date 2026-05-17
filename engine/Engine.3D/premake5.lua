project "Engine.3D"
	kind "StaticLib"
	pchheader "ghe3dpch.h"
	pchsource "src/ghe3dpch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.ixx"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
	}

	links {
		"Core",
		"Engine"
	}
	
	filter "configurations:Debug"
		links {
			library["PhysX_Debug"],
			library["PhysXCommon_Debug"],
			library["PhysXFoundation_Debug"],
			library["PhysXExtensions_Debug"],
			library["PhysXPvdSDK_Debug"]
		}

	filter "configurations:Release"
		links {
			library["PhysX_Release"],
			library["PhysXCommon_Release"],
			library["PhysXFoundation_Release"],
			library["PhysXExtensions_Release"],
			library["PhysXPvdSDK_Release"]
		}
