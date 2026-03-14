project "SystemInfo"
	kind "ConsoleApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine.DirectX",
		"Engine"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"generated/bindings/**.h"
	}

	includedirs {
		"src",
		"generated/bindings",
		includeDir["Core"],
		includeDir["Engine.DirectX"],
		includeDir["Engine"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine.DirectX",
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
