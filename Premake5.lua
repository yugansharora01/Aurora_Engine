workspace "Aurora"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}

IncludeDir["spdlog"] = "Aurora/vendor/spdlog/include"
IncludeDir["imgui"] = "Aurora/vendor/imgui"

project "Aurora"
	location "Aurora"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "Aurora/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"Imgui"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AU_PLATFORM_WINDOWS",
			"AU_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
		}

	filter "configurations:Debug"
		defines "AU_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AU_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "AU_DIST"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AU_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "AU_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AU_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "AU_DIST"
		optimize "On"

include "Aurora/vendor/imgui"