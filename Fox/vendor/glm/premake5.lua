project "GLM"
	language      "C++"
	cppdialect    "C++17"
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

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
