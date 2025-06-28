project "JOLT"
	language      "C++"
	cppdialect    "C++17"
	kind          "StaticLib"
	staticruntime "On"
	
	includedirs
	{
		"include", 
	}
	
	files
	{
		"include/**.h", 
		"include/**.cpp", 
		"include/**.inl", 
	}
	
	disablewarnings
	{
		6385, 
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
