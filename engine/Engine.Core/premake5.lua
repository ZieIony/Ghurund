project "Engine.Core"
	kind "StaticLib"
	pchheader "ghcpch.h"
	pchsource "src/ghcpch.cpp"
	staticruntime "on"

	files {
		"src/**.h",
		"src/**.cpp",
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs {
		"src",
		includeDir["tinyxml2"]
	}

	filter "configurations:Debug"
		links {
			library["tinyxml2_Debug"]
		}

	filter "configurations:Release"
		links {
			library["tinyxml2_Release"]
		}
