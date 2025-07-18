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
