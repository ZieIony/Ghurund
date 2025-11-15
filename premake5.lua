workspace "Ghurund"
	configurations { "Debug", "Release" }
	platforms { "Win64" }
	characterset "Unicode"
	cppdialect "C++latest"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	targetdir "bin/%{cfg.buildcfg}"
	debugdir "$(SolutionDir)"
	defines { "_CRT_SECURE_NO_WARNINGS" }

libsDir = "%{wks.location}/libs"
includeDir = {}
includeDir["Core"] = "%{wks.location}/engine/Core/src"
includeDir["UI"] = "%{wks.location}/engine/UI/src"
includeDir["UI.DirectX"] = "%{wks.location}/engine/UI.DirectX/src"
includeDir["UI.OpenGL"] = "%{wks.location}/engine/UI.OpenGL/src"
includeDir["Engine"] = "%{wks.location}/engine/Engine/src"
includeDir["Engine.DirectX"] = "%{wks.location}/engine/Engine.DirectX/src"
includeDir["Engine.OpenGL"] = "%{wks.location}/engine/Engine.OpenGL/src"
includeDir["UnitTest.Core"] = "%{wks.location}/tests/UnitTest.Core/src"
includeDir["UnitTest.Utils"] = "%{wks.location}/tests/UnitTest.Utils/src"
includeDir["entt"] = "%{libsDir}/entt/single_include/entt"
includeDir["angelscript"] = "%{libsDir}/angelscript_2.36.0/sdk/angelscript/include"
includeDir["msdfgen"] = "%{libsDir}/msdfgen"
includeDir["PhysX"] = "%{libsDir}/PhysX/physx/include"
includeDir["PhysX.Shared"] = "%{libsDir}/PhysX/pxshared/include"
includeDir["CRC"] = "%{libsDir}/CRCpp/inc"
includeDir["DirectX"] = "%{libsDir}"
includeDir["GLEW"] = "%{libsDir}/glew-2.1.0/include"
includeDir["GLFW"] = "%{libsDir}/glfw-3.3.6/include"

libraryDir = {}
libraryDir["angelscript"] = "%{libsDir}/angelscript_2.36.0/sdk/angelscript/lib"
libraryDir["msdfgen_Debug"] = "%{libsDir}/msdfgen/x64/Debug Library"
libraryDir["msdfgen_Release"] = "%{libsDir}/msdfgen/x64/Release Library"
libraryDir["PhysX_Debug"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/debug"
libraryDir["PhysX_Release"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/release"
libraryDir["GLEW"] = "%{libsDir}/glew-2.1.0/lib/Release/x64"
libraryDir["GLFW"] = "%{libsDir}/glfw-3.3.6/lib-vc2022"

library = {}
library["angelscript_Debug"] = "%{libraryDir.angelscript}/angelscript64d.lib"
library["angelscript_Release"] = "%{libraryDir.angelscript}/angelscript64.lib"
library["msdfgen_Debug"] = "%{libraryDir.msdfgen_Debug}/msdfgen.lib"
library["msdfgen_Release"] = "%{libraryDir.msdfgen_Release}/msdfgen.lib"

library["PhysX_Debug"] = "%{libraryDir.PhysX_Debug}/PhysX_64.lib"
library["PhysX_Release"] = "%{libraryDir.PhysX_Release}/PhysX_64.lib"
library["PhysXCommon_Debug"] = "%{libraryDir.PhysX_Debug}/PhysXCommon_64.lib"
library["PhysXCommon_Release"] = "%{libraryDir.PhysX_Release}/PhysXCommon_64.lib"
library["PhysXFoundation_Debug"] = "%{libraryDir.PhysX_Debug}/PhysXFoundation_64.lib"
library["PhysXFoundation_Release"] = "%{libraryDir.PhysX_Release}/PhysXFoundation_64.lib"
library["PhysXExtensions_Debug"] = "%{libraryDir.PhysX_Debug}/PhysXExtensions_static_64.lib"
library["PhysXExtensions_Release"] = "%{libraryDir.PhysX_Release}/PhysXExtensions_static_64.lib"
library["PhysXPvdSDK_Debug"] = "%{libraryDir.PhysX_Debug}/PhysXPvdSDK_static_64.lib"
library["PhysXPvdSDK_Release"] = "%{libraryDir.PhysX_Release}/PhysXPvdSDK_static_64.lib"

library["GLEW"] = "%{libraryDir.GLEW}/glew32.lib"
library["GLFW"] = "%{libraryDir.GLFW}/glfw3_mt.lib"

libdirs = libraryDir

filter { "platforms:Win64" }
    system "Windows"
    architecture "x86_64"
	
filter "configurations:Debug"
	defines { "DEBUG" }
	symbols "On"
	optimize "Off"

filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "Full"

include "apps"
include "engine"
include "samples"
include "tools"
include "tests"
