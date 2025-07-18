project "GLAD"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	includedirs
	{
		"include", 
	}
	
	files
	{
		"include/glad/gl.h", 
		"src/gl.c", 
	}
