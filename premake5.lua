workspace "Cyprium"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cyprium"
	location "Cyprium"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"	
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CP_PLATFORM_WINDOWS",
			"CP_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Cyprium/src"
	}

	links 
	{
		"Cyprium"
	}

	filter "system:windows"
		cppdialect "C++17"	
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "CP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CP_DIST"
		optimize "On"