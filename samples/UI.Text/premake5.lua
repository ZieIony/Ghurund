project "Samples.UI.Text"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Core",
		"UI",
		"UI.DirectX",
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
		includeDir["UI"],
		includeDir["UI.DirectX"],
		includeDir["Engine"],
		includeDir["msdfgen"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"UI",
		"UI.DirectX",
		"Engine"
	}
	
	filter "configurations:Debug"
		links {
			library["msdfgen_Debug"],
			library["PhysX_Debug"],
			library["PhysXCommon_Debug"],
			library["PhysXFoundation_Debug"],
			library["PhysXExtensions_Debug"],
			library["PhysXPvdSDK_Debug"]
		}

	filter "configurations:Release"
		links {
			library["msdfgen_Release"],
			library["PhysX_Release"],
			library["PhysXCommon_Release"],
			library["PhysXFoundation_Release"],
			library["PhysXExtensions_Release"],
			library["PhysXPvdSDK_Release"]
		}
