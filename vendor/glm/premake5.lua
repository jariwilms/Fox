project "GLM"
	language      "C++"
	cppdialect    "C++11"
	kind          "StaticLib"
	staticruntime "On"
	
	includedirs
	{
		"include", 
	}	
	
	files
	{
		"include/glm/**.hpp", 
		"include/glm/**.h", 
		
		"include/glm/**.cpp", 
	}
	
	disablewarnings
	{
		26498, 
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime   "Debug"
		symbols   "On"
		
		targetdir "%{wks.location}/bin/debug/windows/%{prj.name}"
		objdir    "%{wks.location}/build/debug/windows/%{prj.name}"
	
	filter "configurations:Release"
		runtime   "Release"
		optimize  "On"
		
		targetdir "%{wks.location}/bin/release/windows/%{prj.name}"
		objdir    "%{wks.location}/build/release/windows/%{prj.name}"
