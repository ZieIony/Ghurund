project "UI.Direct2D"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.UI",
		"Engine.UI.Direct2D"
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
		includeDir["Engine.UI_bindings"],
		includeDir["Engine.UI.Direct2D"],
		includeDir["tinyxml2"],
	}

	links {
		"Engine.Core",
		"Engine.UI",
		"Engine.UI.Direct2D"
	}
	
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
