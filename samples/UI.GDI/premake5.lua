project "UI.GDI"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.UI",
		"Engine.UI.GDI"
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
		includeDir["Engine.UI"],
		includeDir["Engine.UI.GDI"],
		includeDir["tinyxml2"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["angelscript"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"]
	}

	links {
		"Engine.Core",
		"Engine.UI",
		"Engine.UI.GDI"
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
