project "GLM"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glm/**.hpp", 
		"include/glm/**.h", 
		
		"include/glm/**.cpp", 
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
