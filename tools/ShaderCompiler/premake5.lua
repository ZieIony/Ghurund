project "ShaderCompiler"
	kind "ConsoleApp"
	staticruntime "on"

	dependson {
		"Core",
		"Engine.DirectX",
		"Engine"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"src",
		includeDir["Core"],
		includeDir["Engine.DirectX"],
		includeDir["Engine"],
		includeDir["DirectX"]
	}

	links {
		"Core",
		"Engine.DirectX",
		"Engine"
	}
