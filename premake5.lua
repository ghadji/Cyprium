workspace "Cyprium"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "Cyprium/vendor/glm"
IncludeDir["stb_image"] = "Cyprium/vendor/stb_image"

group "Dependencies"
	include "Cyprium/vendor/GLFW"
	include "Cyprium/vendor/Glad"
	include "Cyprium/vendor/imgui"
group ""

project "Cyprium"
	location "Cyprium"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cppch.h"
	pchsource "Cyprium/src/cppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"	
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CP_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"	
	staticruntime "on"

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
		"Cyprium/vendor",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Cyprium"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CP_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		runtime "Release"
		optimize "on"
