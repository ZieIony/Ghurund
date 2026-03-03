project "Demo.2D.DirectX"
	kind "WindowedApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.2D",
		"Engine.2D.DirectX",
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
		includeDir["Engine.2D"],
		includeDir["Engine.2D.DirectX"],
		includeDir["UI"],
		includeDir["UI.DirectX"],
		includeDir["angelscript"],
		includeDir["Box2D"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine",
		"Engine.DirectX",
		"Engine.2D",
		"Engine.2D.DirectX",
		"UI",
		"UI.DirectX"
	}
	
	filter "configurations:Debug"
		links {
			library["angelscript_Debug"],
			library["Box2D_Debug"]
		}

	filter "configurations:Release"
		links {
			library["angelscript_Release"],
			library["Box2D_Release"]
		}
