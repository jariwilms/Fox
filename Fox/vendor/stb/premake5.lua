project "STB_IMAGE"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

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

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS", 
		
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"