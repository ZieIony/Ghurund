project "Demo.3D.DirectX"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.3D",
		"Engine.3D.DirectX",
		"UI",
		"UI.DirectX"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.DirectX"],
		includeDir["Engine.3D"],
		includeDir["Engine.3D.DirectX"],
		includeDir["UI"],
		includeDir["UI.DirectX"],
		includeDir["PhysX"],
		includeDir["PhysX.Shared"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.3D",
		"Engine.3D.DirectX",
		"UI",
		"UI.DirectX"
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
