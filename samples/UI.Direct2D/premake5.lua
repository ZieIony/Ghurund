project "Samples.UI.Direct2D"
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
		includeDir["Core"],
		includeDir["UI"],
		includeDir["UI.Direct2D"],
		includeDir["tinyxml2"],
	}

	links {
		"Core",
		"UI",
		"UI.Direct2D"
	}
	
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
