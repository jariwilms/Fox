project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h", 
		"include/KHR/khrplatform.h", 
		
		"src/glad.c", 
	}
	
	includedirs
	{
		"include", 
	}	

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
