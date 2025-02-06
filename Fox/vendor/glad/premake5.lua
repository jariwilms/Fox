project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/gl.h", 
		--"include/glad/vulkan.h", 
		--"include/KHR/khrplatform.h", 
		--"include/vk_platform.h", 
		
		"src/gl.c", 
		--"src/vulkan.c", 
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
