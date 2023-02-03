project "ZLIB"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	defines
	{
		"WIN32", 
		"_WINDOWS", 
		"ASSIMP_BUILD_NO_M3D_IMPORTER", 
		"ASSIMP_BUILD_NO_M3D_EXPORTER", 
		"WIN32_LEAN_AND_MEAN", 
		"UNICODE", 
		"_UNICODE", 
		"NO_FSEEKO", 
		"_CRT_SECURE_NO_DEPRECATE", 
		"_CRT_NONSTDC_NO_DEPRECATE", 
		"CMAKE_INTDIR='Debug'", 
	}
	
	files
	{
		"./*.h", 
		"./*.c", 
	}
	
	includedirs
	{
		"contrib", 
		"win32", 
	}
	
	buildoptions
	{
		"%(AdditionalOptions) /bigobj", 
	}

	
	filter "system:windows"
		systemversion "latest"

	filter  "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter  "configurations:Release"
		runtime "Release"
		optimize "On"