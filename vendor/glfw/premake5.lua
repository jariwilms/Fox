project "GLFW"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	includedirs
	{
		"./", 
		
		"%{prj.name}/src", 
	}
	
	files
	{
		"include/glfw/*", 
		"src/*", 
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines 
		{ 
			"_GLFW_WIN32",
		}
	
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
