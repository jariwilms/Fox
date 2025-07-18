project "ASSIMP"
	language        "C++"
	cppdialect      "C++17"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "Off"
	buildstlmodules "Off"
	warnings        "Off"
	
	defines
	{
		"WIN32", 
		"_WINDOWS", 
		"WIN32_LEAN_AND_MEAN", 
		
		"UNICODE", 
		"_UNICODE", 
		
		"OPENDDL_STATIC_LIBARY", 
		"P2T_STATIC_EXPORTS", 
		"OPENDDLPARSER_BUILD", 
		"RAPIDJSON_HAS_STDSTRING=1", 
		"RAPIDJSON_NOMEMBERITERATORCLASS", 
		
		"ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1", 
		
		"ASSIMP_BUILD_NO_3DS_EXPORTER", 
		"ASSIMP_BUILD_NO_3DS_IMPORTER", 
		"ASSIMP_BUILD_NO_3D_IMPORTER", 
		"ASSIMP_BUILD_NO_3MF_EXPORTER", 
		"ASSIMP_BUILD_NO_3MF_IMPORTER", 
		"ASSIMP_BUILD_NO_AC_IMPORTER", 
		"ASSIMP_BUILD_NO_AMF_IMPORTER", 
		"ASSIMP_BUILD_NO_ASE_IMPORTER", 
		"ASSIMP_BUILD_NO_ASSBIN_EXPORTER", 
		"ASSIMP_BUILD_NO_ASSBIN_IMPORTER", 
		"ASSIMP_BUILD_NO_ASSJSON_EXPORTER", 
		"ASSIMP_BUILD_NO_ASSXML_EXPORTER", 
		"ASSIMP_BUILD_NO_B3D_IMPORTER", 
		"ASSIMP_BUILD_NO_BLEND_IMPORTER", 
		"ASSIMP_BUILD_NO_BVH_IMPORTER", 
		"ASSIMP_BUILD_NO_C4D_IMPORTER", 
		"ASSIMP_BUILD_NO_COB_IMPORTER", 
		"ASSIMP_BUILD_NO_COLLADA_EXPORTER", 
		"ASSIMP_BUILD_NO_COLLADA_IMPORTER", 
		"ASSIMP_BUILD_NO_CSM_IMPORTER", 
		"ASSIMP_BUILD_NO_DXF_IMPORTER", 
		"ASSIMP_BUILD_NO_FBX_EXPORTER", 
		--"ASSIMP_BUILD_NO_FBX_IMPORTER", 
		"ASSIMP_BUILD_NO_GLTF_EXPORTER", 
		--"ASSIMP_BUILD_NO_GLTF_IMPORTER", 
		"ASSIMP_BUILD_NO_HMP_IMPORTER", 
		"ASSIMP_BUILD_NO_IFC_IMPORTER", 
		"ASSIMP_BUILD_NO_IQM_IMPORTER", 
		"ASSIMP_BUILD_NO_IRRMESH_IMPORTER", 
		"ASSIMP_BUILD_NO_IRR_IMPORTER", 
		"ASSIMP_BUILD_NO_LWO_IMPORTER", 
		"ASSIMP_BUILD_NO_LWS_IMPORTER", 
		"ASSIMP_BUILD_NO_M3D_EXPORTER", 		
		"ASSIMP_BUILD_NO_M3D_IMPORTER", 
		"ASSIMP_BUILD_NO_MD2_IMPORTER", 
		"ASSIMP_BUILD_NO_MD3_IMPORTER", 
		"ASSIMP_BUILD_NO_MD5_IMPORTER", 
		"ASSIMP_BUILD_NO_MDC_IMPORTER", 
		"ASSIMP_BUILD_NO_MDL_IMPORTER", 
		"ASSIMP_BUILD_NO_MMD_IMPORTER", 
		"ASSIMP_BUILD_NO_MS3D_IMPORTER", 
		"ASSIMP_BUILD_NO_NDO_IMPORTER", 
		"ASSIMP_BUILD_NO_NFF_IMPORTER", 
		"ASSIMP_BUILD_NO_OBJ_EXPORTER", 
		--"ASSIMP_BUILD_NO_OBJ_IMPORTER", 
		"ASSIMP_BUILD_NO_OFF_IMPORTER", 
		"ASSIMP_BUILD_NO_OGRE_IMPORTER", 
		"ASSIMP_BUILD_NO_OPENGEX_EXPORTER", 
		"ASSIMP_BUILD_NO_OPENGEX_IMPORTER", 
		"ASSIMP_BUILD_NO_PBRT_EXPORTER", 
		"ASSIMP_BUILD_NO_PLY_EXPORTER", 
		"ASSIMP_BUILD_NO_PLY_IMPORTER", 
		"ASSIMP_BUILD_NO_Q3BSP_IMPORTER", 
		"ASSIMP_BUILD_NO_Q3D_IMPORTER", 
		"ASSIMP_BUILD_NO_RAW_IMPORTER", 
		"ASSIMP_BUILD_NO_SIB_IMPORTER", 
		"ASSIMP_BUILD_NO_SMD_IMPORTER", 
		"ASSIMP_BUILD_NO_STEP_EXPORTER", 
		"ASSIMP_BUILD_NO_STL_EXPORTER", 
		"ASSIMP_BUILD_NO_STL_IMPORTER", 
		"ASSIMP_BUILD_NO_TERRAGEN_IMPORTER", 
		"ASSIMP_BUILD_NO_USD_IMPORTER", 
		"ASSIMP_BUILD_NO_X3D_EXPORTER", 
		"ASSIMP_BUILD_NO_X3D_IMPORTER", 
		"ASSIMP_BUILD_NO_XGL_IMPORTER", 
		"ASSIMP_BUILD_NO_X_EXPORTER", 
		"ASSIMP_BUILD_NO_X_IMPORTER", 
	}
	
	includedirs 
	{
		"./", 
		
		"code", 
		"include", 
		
		"contrib", 
		"contrib/irrXML",
		"contrib/openddlparser/include", 
		"contrib/pugixml/src",
		"contrib/rapidjson/include",
		"contrib/stb", 
		"contrib/unzip", 
		"contrib/utf8cpp/source", 
		"contrib/zlib", 
	}
	
	files 
	{
		"include/**",
		
		"code/AssetLib/FBX/**", 
		"code/AssetLib/Obj/**", 
		"code/AssetLib/glTF/**", 
		"code/AssetLib/glTF2/**", 
		
		"code/CApi/*", 
		"code/Common/*", 
		"code/Geometry/*", 
		"code/Material/*", 
		"code/PostProcessing/*", 
		
		"contrib/Open3DGC/*", 
		"contrib/pugixml/src/*", 
		"contrib/unzip/*", 
		"contrib/zip/src/*", 
		"contrib/zlib/*", 
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
