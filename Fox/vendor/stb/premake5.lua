project "STB_IMAGE"
	language      "C"
	kind          "StaticLib"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS", 
		
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
	}

	files
	{
		"include/stb/stb_image.h", 
		"include/stb/stb_image_write.h", 
		
		"src/stb_image.c", 
	}
	
	includedirs
	{
		"include/stb", 
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
