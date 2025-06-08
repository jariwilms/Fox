project "ENTT"
	language      "C++"
	cppdialect    "C++17"
	kind          "StaticLib"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")

	files
	{
		"include/**", 
		"src/**", 
	}

	includedirs
	{
		"include", 
		"src", 
	}

	disablewarnings
	{
		26827, 
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
