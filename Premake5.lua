workspace "Aurora"
	architecture "x64"
	startproject "Aurora-Editor"

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
IncludeDir["yaml_cpp"] = "Aurora/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Aurora/vendor/ImGuizmo"

project "Aurora"
	location "Aurora"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "Aurora/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/Platform/Windows/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"ImGui",
		"yaml-cpp"
	}

	filter "files:Aurora/vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }

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


project "Aurora-Editor"
	location "Aurora-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "Editorpch.h"
	pchsource "Aurora-Editor/src/Editorpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Aurora/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
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


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
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
		"Aurora/vendor/ImGui",
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
include "Aurora/vendor/yaml-cpp"