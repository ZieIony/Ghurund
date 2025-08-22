project "Demo.3D.OpenGL"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.OpenGL"
	}

	files {
		"src/**.h",
		"src/**.cpp",
		"generated/bindings/**.h"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.OpenGL"],
		includeDir["tinyxml2"],
		includeDir["entt"],
		includeDir["CRC"],
		includeDir["angelscript"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"]
	}

	links {
		"Core",
		"Engine",
		"Engine.OpenGL"
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
