project "BindingGenerator"
	configurations { "Debug", "Release" }
	language "C#"
	kind "ConsoleApp"
	dotnetframework "net4.8"
	csversion "8.0"
	entrypoint "BindingGenerator.Program"
	
	files {
		"src/**.cs"
	}
