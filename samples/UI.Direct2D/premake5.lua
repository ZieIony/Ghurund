project "Samples.UI.Direct2D"
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
		"generated/bindings/**.h"
	}

	includedirs {
		"src",
		"generated/bindings",
		includeDir["Core"],
		includeDir["Engine"],
		includeDir["Engine.DirectX"],
		includeDir["UI"],
		includeDir["UI.Direct2D"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine.DirectX",
		"UI",
		"UI.Direct2D",
		"Engine"
	}
