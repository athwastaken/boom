workspace "boom"
	architecture "x64"

	startproject "boom"

	configurations
	{
		"debug",
		"release",
		"dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	includedir = {}
	includedir["glfw"] = "boomEngine/vendor/glfw/include"
	includedir["glad"] = "boomEngine/vendor/glad/include"
	includedir["spdlog"] = "boomEngine/vendor/spdlog/include"
	includedir["imgui"] = "boomEngine/vendor/imgui"

	group "dependencies"
		include "boomEngine/vendor/glfw"
		include "boomEngine/vendor/glad"
		include "boomEngine/vendor/imgui"
	group ""


project "boomEngine"
	location "boomEngine"
	kind "SharedLib"
	staticruntime "off"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bmpch.h"
	pchsource "%{prj.name}/src/bmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{includedir.spdlog}",
		"%{includedir.glfw}",
		"%{includedir.glad}",
		"%{includedir.imgui}"
	}

	links
	{
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"BM_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/boom/\"")
		}
	
	filter "configurations:debug"
		defines "BM_DEBUG"
		runtime "debug"
		symbols "On"
		

	filter "configurations:release"
		defines "BM_RELEASE"
		runtime "release"
		optimize "On"

	filter "configurations:dist"
		defines "BM_DIST"
		runtime "release"
		optimize "On"
		symbols "Off"

project "boom"
	location "boom"
	kind "ConsoleApp"
	staticruntime "off"
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
		"boomEngine/src",
		"%{includedir.spdlog}",
		"%{includedir.glfw}",
		"%{includedir.glad}",
		"%{includedir.imgui}"
		
	}

	links
	{
		"boomEngine"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"BM_PLATFORM_WINDOWS"
		}
	
	filter "configurations:debug"
		defines "BM_DEBUG"
		runtime "debug"
		symbols "On"
		

	filter "configurations:release"
		defines "BM_RELEASE"
		runtime "release"
		optimize "On"

	filter "configurations:dist"
		defines "BM_DIST"
		runtime "release"
		optimize "On"
		symbols "Off"