project "Engine"
	kind "StaticLib"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.Core.DirectX",
		"Engine.UI",
		"Engine.UI.Direct2D"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["Engine.Core.DirectX"],
		includeDir["Engine.UI"],
		includeDir["Engine.UI.Direct2D"],
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
		"Engine.UI.Direct2D"
	}
	
	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"],
			library["angelscript_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"],
			library["angelscript_Release"]
		}
