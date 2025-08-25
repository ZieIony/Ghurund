project "Preview"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine.DirectX",
		"UI",
		"UI.Direct2D",
		"Engine"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"src/**.ixx",
		"generated/bindings/**.h"
	}

	includedirs {
		"src",
		"generated/bindings",
		includeDir["Core"],
		includeDir["Engine.DirectX"],
		includeDir["UI"],
		includeDir["UI.Direct2D"],
		includeDir["Engine"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["angelscript"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine.DirectX",
		"UI",
		"UI.Direct2D",
		"Engine"
	}
	
	filter "configurations:Debug"
		links {
			library["angelscript_Debug"],
			library["PhysX_Debug"],
			library["PhysXCommon_Debug"],
			library["PhysXFoundation_Debug"],
			library["PhysXExtensions_Debug"],
			library["PhysXPvdSDK_Debug"]
		}

	filter "configurations:Release"
		links {
			library["angelscript_Release"],
			library["PhysX_Release"],
			library["PhysXCommon_Release"],
			library["PhysXFoundation_Release"],
			library["PhysXExtensions_Release"],
			library["PhysXPvdSDK_Release"]
		}
