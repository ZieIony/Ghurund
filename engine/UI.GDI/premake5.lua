project "UI.GDI"
	kind "StaticLib"
	pchheader "ghuigdipch.h"
	pchsource "src/ghuigdipch.cpp"
	staticruntime "on"

	dependson {
		"Core",
		"UI"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["UI"],
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