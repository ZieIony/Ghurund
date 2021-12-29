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
includeDir["Engine.Core"] = "%{wks.location}/engine/Engine.Core/src"
includeDir["Engine.Core.DirectX"] = "%{wks.location}/engine/Engine.Core.DirectX/src"
includeDir["Engine.UI"] = "%{wks.location}/engine/Engine.UI/src"
includeDir["Engine.UI_bindings"] = "%{wks.location}/engine/Engine.UI/generated/bindings"
includeDir["Engine.UI.Direct2D"] = "%{wks.location}/engine/Engine.UI.Direct2D/src"
includeDir["Engine.UI.GDI"] = "%{wks.location}/engine/Engine.UI.GDI/src"
includeDir["Engine"] = "%{wks.location}/engine/Engine/src"
includeDir["tinyxml2"] = "%{libsDir}/tinyxml2"
includeDir["entt"] = "%{libsDir}/entt/single_include/entt"
includeDir["angelscript"] = "%{libsDir}/angelscript_2.33.0/sdk/angelscript/include"
includeDir["PhysX"] = "%{libsDir}/PhysX/physx/include"
includeDir["PhysX.Shared"] = "%{libsDir}/PhysX/pxshared/include"
includeDir["CRC"] = "%{libsDir}/CRCpp/inc"
includeDir["DirectX"] = "%{libsDir}"

libraryDir = {}
libraryDir["tinyxml2_Debug"] = "%{libsDir}/tinyxml2/vs/x64/Debug"
libraryDir["tinyxml2_Release"] = "%{libsDir}/tinyxml2/vs/x64/Release"
libraryDir["angelscript"] = "%{libsDir}/angelscript_2.33.0/sdk/angelscript/lib"
libraryDir["PhysX_Debug"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/debug"
libraryDir["PhysX_Release"] = "%{libsDir}/PhysX/physx/bin/win.x86_64.vc141.mt/release"

library = {}
library["tinyxml2_Debug"] = "%{libraryDir.tinyxml2_Debug}/tinyxml2d64.lib"
library["tinyxml2_Release"] = "%{libraryDir.tinyxml2_Release}/tinyxml264.lib"
library["angelscript_Debug"] = "%{libraryDir.angelscript}/angelscript64d.lib"
library["angelscript_Release"] = "%{libraryDir.angelscript}/angelscript64.lib"

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
