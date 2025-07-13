project "GLM"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	buildstlmodules "On"

	defines
	{
		"GLM_ENABLE_EXPERIMENTAL", 
		
		"GLM_GTC_INLINE_NAMESPACE", 
		"GLM_EXT_INLINE_NAMESPACE", 
		"GLM_GTX_INLINE_NAMESPACE", 
	}

	includedirs
	{
		"include", 
	}	
	
	files
	{
		"include/glm/**.hpp", 
		"include/glm/**.cpp", 
		"include/glm/**.inl", 
		"include/glm/**.ixx", 
	}
	
	disablewarnings
	{
		26498, 
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
