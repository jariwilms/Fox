project "JOLT"
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
	}
	
	files
	{
		"include/**.h", 
		"include/**.cpp", 
		"include/**.inl", 
	}
