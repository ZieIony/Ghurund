project "Engine.UI"
	kind "StaticLib"
	pchheader "ghuipch.h"
	pchsource "src/ghuipch.cpp"
	staticruntime "on"

	dependson { "Engine.Core" }

	files {
		"src/**.h",
		"src/**.cpp",
		"generated/bindings/**.h"
	}

	includedirs {
		includeDir["Engine.UI"],
		includeDir["Engine.Core"],
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