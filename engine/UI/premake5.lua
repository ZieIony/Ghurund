project "UI"
	kind "StaticLib"
	pchheader "ghuipch.h"
	pchsource "src/ghuipch.cpp"
	staticruntime "on"
	buildoptions { "/Zc:__cplusplus" }

	dependson {
		"Core",
		"Engine"
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
		includeDir["msdfgen"]
	}
	
	links {
		"Core",
		"Engine"
	}

	filter "configurations:Debug"
		links {
			library["msdfgen_Debug"]
		}

	filter "configurations:Release"
		links {
			library["msdfgen_Release"]
		}