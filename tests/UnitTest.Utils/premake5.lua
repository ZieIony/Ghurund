project "UnitTest.Utils"
	kind "StaticLib"
	staticruntime "on"

	dependson {
		"Core"
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		includeDir["Core"]
	}

	links {
		"Core"
	}
