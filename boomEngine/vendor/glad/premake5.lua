project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/khr/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:debug"
		runtime "debug"
		symbols "on"

	filter "configurations:release"
		runtime "release"
		optimize "on"

	filter "configurations:dist"
		runtime "release"
		optimize "on"
        symbols "off"