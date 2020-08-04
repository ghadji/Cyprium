workspace "Cyprium"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include folders that are relative to the root folder 
IncludeDir = {}
IncludeDir["GLFW"] = "Cyprium/vendor/GLFW/include"
IncludeDir["Glad"] = "Cyprium/vendor/Glad/include"
IncludeDir["ImGui"] = "Cyprium/vendor/imgui"

include "Cyprium/vendor/GLFW"
include "Cyprium/vendor/Glad"
include "Cyprium/vendor/imgui"

project "Cyprium"
	location "Cyprium"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cppch.h"
	pchsource "Cyprium/src/cppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CP_PLATFORM_WINDOWS",
			"CP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CP_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Cyprium/vendor/spdlog/include",
		"Cyprium/src",
		"Cyprium/vendor"
	}

	links 
	{
		"Cyprium"
	}

	filter "system:windows"
		cppdialect "C++17"	
		systemversion "latest"

		defines
		{
			"CP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CP_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		runtime "Release"
		optimize "On"