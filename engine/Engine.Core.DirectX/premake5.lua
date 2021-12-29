project "Engine.Core.DirectX"
	kind "StaticLib"
	pchheader "ghcdxpch.h"
	pchsource "src/ghcdxpch.cpp"
	staticruntime "on"

	dependson {
		"Engine.Core"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs {
		"src",
		includeDir["Engine.Core"],
		includeDir["DirectX"]
	}

	links {
		"Engine.Core"
	}
	