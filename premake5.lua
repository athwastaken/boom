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
	includedir["GLFW"] = "boomEngine/vendor/GLFW/include/"
	includedir["Glad"] = "boomEngine/vendor/Glad/include/"
	includedir["spdlog"] = "boomEngine/vendor/spdlog/include/"
	includedir["ImGui"] = "boomEngine/vendor/TheCherno/ImGui"
	includedir["glm"] = "boomEngine/vendor/glm/"

	group "dependencies"
		include "boomEngine/vendor/GLFW/"
		include "boomEngine/vendor/Glad/"
		include "boomEngine/vendor/TheCherno/ImGui/"
	group ""


project "boomEngine"
	location "boomEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bmpch.h"
	pchsource "%{prj.name}/src/bmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src/",
		"%{includedir.spdlog}",
		"%{includedir.GLFW}",
		"%{includedir.Glad}",
		"%{includedir.ImGui}",
		"%{includedir.glm}"
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
			"BM_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
		}
	
	filter "configurations:debug"
		defines "BM_DEBUG"
		runtime "debug"
		symbols "on"
		

	filter "configurations:release"
		defines "BM_RELEASE"
		runtime "release"
		optimize "on"

	filter "configurations:dist"
		defines "BM_DIST"
		runtime "release"
		optimize "on"

project "boom"
	location "boom"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
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
		"boomEngine/src",
		"%{includedir.spdlog}",
		"%{includedir.GLFW}",
		"%{includedir.Glad}",
		"%{includedir.ImGui}",
		"%{includedir.glm}"
	}

	links
	{
		"boomEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BM_PLATFORM_WINDOWS"
		}
	
	filter "configurations:debug"
		defines "BM_DEBUG"
		runtime "debug"
		symbols "on"
		

	filter "configurations:release"
		defines "BM_RELEASE"
		runtime "release"
		optimize "on"

	filter "configurations:dist"
		defines "BM_DIST"
		runtime "release"
		optimize "on"
