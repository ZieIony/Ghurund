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
includeDir["Engine.2D"] = "%{wks.location}/engine/Engine.2D/src"
includeDir["Engine.2D.DirectX"] = "%{wks.location}/engine/Engine.2D.DirectX/src"
includeDir["Engine.3D"] = "%{wks.location}/engine/Engine.3D/src"
includeDir["Engine.3D.DirectX"] = "%{wks.location}/engine/Engine.3D.DirectX/src"
includeDir["UnitTest.Core"] = "%{wks.location}/tests/UnitTest.Core/src"
includeDir["UnitTest.Utils"] = "%{wks.location}/tests/UnitTest.Utils/src"
includeDir["entt"] = "%{libsDir}/entt/single_include/entt"
includeDir["msdfgen"] = "%{libsDir}/msdfgen"
includeDir["Box2D"] = "%{libsDir}/box2d-3.1.1/include/box2d"
includeDir["PhysX"] = "%{libsDir}/PhysX/physx/include"
includeDir["PhysX.Shared"] = "%{libsDir}/PhysX/pxshared/include"
includeDir["CRC"] = "%{libsDir}/CRCpp/inc"
includeDir["DirectX"] = "%{libsDir}"
includeDir["GLEW"] = "%{libsDir}/glew-2.1.0/include"
includeDir["GLFW"] = "%{libsDir}/glfw-3.3.6/include"
includeDir["assimp"] = "%{libsDir}/assimp/include"

libraryDir = {}
libraryDir["msdfgen_Debug"] = "%{libsDir}/msdfgen/x64/Debug Library"
libraryDir["msdfgen_Release"] = "%{libsDir}/msdfgen/x64/Release Library"
libraryDir["Box2D_Debug"] = "%{libsDir}/box2d-3.1.1/build/src/Debug"
libraryDir["Box2D_Release"] = "%{libsDir}/box2d-3.1.1/build/src/Release"
libraryDir["PhysX_Debug"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/debug"
libraryDir["PhysX_Release"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/release"
libraryDir["GLEW"] = "%{libsDir}/glew-2.1.0/lib/Release/x64"
libraryDir["GLFW"] = "%{libsDir}/glfw-3.3.6/lib-vc2022"
libraryDir["assimp"] = "%{libsDir}/assimp/lib"

library = {}
library["msdfgen_Debug"] = "%{libraryDir.msdfgen_Debug}/msdfgen.lib"
library["msdfgen_Release"] = "%{libraryDir.msdfgen_Release}/msdfgen.lib"
library["Box2D_Debug"] = "%{libraryDir.Box2D_Debug}/box2dd.lib"
library["Box2D_Release"] = "%{libraryDir.Box2D_Release}/box2d.lib"

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
library["assimp_Debug"] = "%{libraryDir.assimp}/debug/assimp-vc143-mtd.lib"
library["assimp_Release"] = "%{libraryDir.assimp}/release/assimp-vc143-mt.lib"
library["draco_Debug"] = "%{libraryDir.assimp}/debug/draco.lib"
library["draco_Release"] = "%{libraryDir.assimp}/release/draco.lib"
library["kubazip_Debug"] = "%{libraryDir.assimp}/debug/kubazip.lib"
library["kubazip_Release"] = "%{libraryDir.assimp}/release/kubazip.lib"
library["minizip_Debug"] = "%{libraryDir.assimp}/debug/minizip.lib"
library["minizip_Release"] = "%{libraryDir.assimp}/release/minizip.lib"
library["poly2tri_Debug"] = "%{libraryDir.assimp}/debug/poly2tri.lib"
library["poly2tri_Release"] = "%{libraryDir.assimp}/release/poly2tri.lib"
library["polyclipping_Debug"] = "%{libraryDir.assimp}/debug/polyclipping.lib"
library["polyclipping_Release"] = "%{libraryDir.assimp}/release/polyclipping.lib"
library["pugixml_Debug"] = "%{libraryDir.assimp}/debug/pugixml.lib"
library["pugixml_Release"] = "%{libraryDir.assimp}/release/pugixml.lib"
library["zlib_Debug"] = "%{libraryDir.assimp}/debug/zlibd.lib"
library["zlib_Release"] = "%{libraryDir.assimp}/release/zlib.lib"

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
