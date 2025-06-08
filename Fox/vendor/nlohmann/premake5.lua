project "NLOHMANN"
	language      "C++"
	cppdialect    "C++17"
	kind          "StaticLib"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")
	
	files
	{
		"include/nlohmann/json.hpp", 
	}
	
	includedirs
	{
		"include", 
	}

	disablewarnings
	{
		26819, 
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
