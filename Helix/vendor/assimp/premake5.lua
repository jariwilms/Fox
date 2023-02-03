project "ASSIMP"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	defines
	{
		"ASSIMP_BUILD_DLL_EXPORT", 
		"ASSIMP_BUILD_NO_C4D_IMPORTER", 
		"ASSIMP_BUILD_NO_M3D_EXPORTER", 
		"ASSIMP_BUILD_NO_M3D_IMPORTER", 
		"ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1", 
		"CMAKE_INTDIR='Debug'", 
		"MINIZ_USE_UNALIGNED_LOADS_AND_STORES=0", 
		"OPENDDLPARSER_BUILD", 
		"RAPIDJSON_HAS_STDSTRING=1", 
		"RAPIDJSON_NOMEMBERITERATORCLASS", 
		"UNICODE", 
		"WIN32", 
		"WIN32_LEAN_AND_MEAN", 
		"_CRT_SECURE_NO_WARNINGS", 
		"_DEBUG", 
		"_SCL_SECURE_NO_WARNINGS", 
		"_UNICODE", 
		"_WINDOWS", 
		"assimp_EXPORTS", 
	}
	
	files
	{
		"include/**", 
		"code/**", 
	}
	
	includedirs
	{
		"./", 
		"../zlib", 
		
		"include", 
		"code", 
		"contrib", 
		"contrib/unzip", 
		"contrib/pugixml/src", 
		"contrib/rapidjson/include", 
		"contrib/openddlparser/include", 
	}
	
	links
	{		
		"ZLIB", 
		
		"kernel32.lib", 
		"user32.lib", 
		"gdi32.lib", 
		"winspool.lib", 
		"shell32.lib", 
		"ole32.lib", 
		"oleaut32.lib", 
		"uuid.lib", 
		"comdlg32.lib", 
		"advapi32.lib", 
	}
	
	disablewarnings
	{
		"4006", 
		"4244", 
		"4996", 
		"26451", 
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