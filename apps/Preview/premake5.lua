project "Preview"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.Core.DirectX",
		"Engine.UI",
		"Engine.UI.Direct2D",
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
		includeDir["Engine.Core"],
		includeDir["Engine.Core.DirectX"],
		includeDir["Engine.UI"],
		includeDir["Engine.UI.Direct2D"],
		includeDir["Engine"],
		includeDir["tinyxml2"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["angelscript"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Engine.Core",
		"Engine.Core.DirectX",
		"Engine.UI",
		"Engine.UI.Direct2D",
		"Engine"
	}
	
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"],
			library["angelscript_Debug"],
			library["PhysX_Debug"],
			library["PhysXCommon_Debug"],
			library["PhysXFoundation_Debug"],
			library["PhysXExtensions_Debug"],
			library["PhysXPvdSDK_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"],
			library["angelscript_Release"],
			library["PhysX_Release"],
			library["PhysXCommon_Release"],
			library["PhysXFoundation_Release"],
			library["PhysXExtensions_Release"],
			library["PhysXPvdSDK_Release"]
		}
