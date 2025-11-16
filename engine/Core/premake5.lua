project "Core"
	kind "StaticLib"
	pchheader "ghcpch.h"
	pchsource "src/ghcpch.cpp"
	staticruntime "on"
	buildoptions { "/Zc:__cplusplus" }

	files {
		"src/**.h",
		"src/**.cpp"
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs {
		"src"
	}
	
	links {
		"tinyxml2",
		"Xinput",
		"Xinput9_1_0"
	}
	