project "GLFW"
	language      "C"
	kind          "StaticLib"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")

	defines
	{
		"_CRT_SECURE_NO_WARNINGS", 
	}

	files
	{
		"include/glfw/*", 
		"src/*", 
	}

	includedirs
	{
		"./", 
		
		"%{prj.name}/src", 
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"_GLFW_WIN32",
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
