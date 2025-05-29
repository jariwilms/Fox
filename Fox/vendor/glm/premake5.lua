project "GLM"
	language      "C++"
	cppdialect    "C++11"
	kind          "StaticLib"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")
	
	files
	{
		"include/glm/**.hpp", 
		"include/glm/**.h", 
		
		"include/glm/**.cpp", 
	}
	
	includedirs
	{
		"include", 
	}	

	disablewarnings
	{
		26498, 
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
