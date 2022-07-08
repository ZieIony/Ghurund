project "Engine.UI.GDI"
	kind "StaticLib"
	pchheader "ghuigdipch.h"
	pchsource "src/ghuigdipch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core",
		"Engine.UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["Engine.UI"],
		includeDir["tinyxml2"],
		includeDir["msdfgen"]
	}

	filter "configurations:Debug"
		links {
			library["msdfgen_Debug"]
		}

	filter "configurations:Release"
		links {
			library["msdfgen_Release"]
		}