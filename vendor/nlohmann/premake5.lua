project "NLOHMANN"
	language        "C++"
	cppdialect      "C++11"
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
		"include/nlohmann/json.hpp", 
		"source/json.cpp", 
	}
