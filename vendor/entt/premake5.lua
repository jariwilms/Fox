project "ENTT"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "Off"
	buildstlmodules "Off"
	warnings        "Off"
	
	includedirs
	{
		"include", 
		"src", 
	}
	
	files
	{
		"include/**", 
		"src/**", 
	}
