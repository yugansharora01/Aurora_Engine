workspace "Aurora"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

IncludeDir["spdlog"] = "Aurora/vendor/spdlog/include"
IncludeDir["imgui"] = "Aurora/vendor/imgui"

project "Aurora"
	location "Aurora"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "Aurora/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/Platform/Windows/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AU_PLATFORM_WINDOWS",
			"AU_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "AU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AU_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "AU_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Aurora/vendor/spdlog/include",
		"Aurora/src"
	}

	links
	{
		"Aurora"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AU_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "AU_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "AU_DIST"
		runtime "Release"
		optimize "On"

include "Aurora/vendor/imgui"