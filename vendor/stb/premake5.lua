project "STB"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	defines 
	{
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
