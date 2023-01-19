project "TINYGLTF"
	kind "StaticLib"
	language "C"
	cppdialect "C++11"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/tinygltf/*.h", 
		"include/tinygltf/*.hpp", 
		"include/tinygltf/*.cc", 
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
