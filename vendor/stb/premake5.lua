project "STB_IMAGE"
	language      "C"
	kind          "StaticLib"
	staticruntime "On"
	
	defines 
	{
		"_CRT_SECURE_NO_WARNINGS", 
		
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
	}

	includedirs
	{
		"include/stb", 
	}
	
	files
	{
		"include/stb/stb_image.h", 
		"include/stb/stb_image_write.h", 
		
		"src/stb_image.c", 
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
