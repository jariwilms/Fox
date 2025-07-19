workspace "Fox Engine"
	architecture "x64"
	startproject "RUN"
	
	configurations { 
		"Debug", 
		"Release", 
	}
	
	includedir = {
		["ASSIMP"  ] = "vendor/assimp/include", 
		["ENTT"    ] = "vendor/entt/include", 
		["GLAD"    ] = "vendor/glad/include", 
		["GLFW"    ] = "vendor/glfw/include", 
		["GLM"     ] = "vendor/glm", 
		["JOLT"    ] = "vendor/jolt/include", 
		["MIMALLOC"] = "vendor/mimalloc/include", 
		["NLOHMANN"] = "vendor/nlohmann/include", 
		["STB"     ] = "vendor/stb/include", 
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

	--
	-- @brief Visual Studio: Bugfix for C++ Modules (same module file name per project)
	-- Credit goes to larioteo
	-- https://github.com/premake/premake-core/issues/2177
	--
	require("vstudio")
	premake.override(premake.vstudio.vc2010.elements, "clCompile", function(base, prj)
		local m     = premake.vstudio.vc2010
		local calls = base(prj)
		
		if premake.project.iscpp(prj) and string.find(prj.filename, "FOX") then
			table.insertafter(calls, premake.xmlDeclaration,  function()
				premake.w('<ModuleDependenciesFile>$(IntDir)\\%%(RelativeDir)</ModuleDependenciesFile>')
				premake.w('<ModuleOutputFile>$(IntDir)\\%%(RelativeDir)</ModuleOutputFile>')
				premake.w('<ObjectFileName>$(IntDir)\\%%(RelativeDir)</ObjectFileName>')
			end)
		end

		return calls
	end)



group "Dependencies"
project "ASSIMP"
	location        "vendor/assimp"
	language        "C++"
	cppdialect      "C++17"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "Off"
	buildstlmodules "Off"
	warnings        "Off"
	
	defines {
		"CMAKE_INTDIR='Debug'", 
		"OPENDDLPARSER_BUILD", 
		"OPENDDL_STATIC_LIBARY", 
		"P2T_STATIC_EXPORTS", 
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
		"ASSIMP_BUILD_NO_FBX_IMPORTER", 
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
		"ASSIMP_BUILD_NO_OBJ_IMPORTER", 
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
		"ASSIMP_BUILD_NO_VRML_IMPORTER", 
		"ASSIMP_BUILD_NO_X3D_EXPORTER", 
		"ASSIMP_BUILD_NO_X3D_IMPORTER", 
		"ASSIMP_BUILD_NO_XGL_IMPORTER", 
		"ASSIMP_BUILD_NO_X_EXPORTER", 
		"ASSIMP_BUILD_NO_X_IMPORTER", 
		"ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1", 
	}
	
	includedirs {
		"%{prj.location}", 
		"%{prj.location}/.", 
		"%{prj.location}/code", 
		"%{prj.location}/code/..", 
		"%{prj.location}/code/../contrib", 
		"%{prj.location}/code/../contrib/openddlparser/include", 
		"%{prj.location}/code/../contrib/pugixml/src", 
		"%{prj.location}/code/../contrib/rapidjson/include", 
		"%{prj.location}/code/../contrib/unzip", 
		"%{prj.location}/code/../contrib/utf8cpp/source", 
		"%{prj.location}/code/../include", 
		"%{prj.location}/code/../include", 
		"%{prj.location}/contrib/zlib", 
		"%{prj.location}/contrib/zlib", 
		"%{prj.location}/include", 
		"%{prj.location}/include", 
	}
	
	files {
		"%{prj.location}/code/AssetLib/STEPParser/**", 
		"%{prj.location}/code/AssetLib/glTF/**", 
		"%{prj.location}/code/AssetLib/glTF2/**", 
		"%{prj.location}/code/AssetLib/glTFCommon/**", 
		"%{prj.location}/code/CApi/**", 
		"%{prj.location}/code/Common/**", 
		"%{prj.location}/code/Geometry/**", 
		"%{prj.location}/code/Material/**", 
		"%{prj.location}/code/PostProcessing/**", 
		"%{prj.location}/contrib/Open3DGC/**", 
		"%{prj.location}/contrib/clipper/**", 
		"%{prj.location}/contrib/openddlparser/**", 
		"%{prj.location}/contrib/poly2tri/**", 
		"%{prj.location}/contrib/pugixml/**", 
		"%{prj.location}/contrib/stb/**", 
		"%{prj.location}/contrib/unzip/**", 
		"%{prj.location}/include/assimp/**", 
		"%{prj.location}/include/assimp/Compiler/**", 
	}



include "vendor/entt"
include "vendor/glad"
include "vendor/glfw"



project "GLM"
	location        "vendor/glm"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "On"
	buildstlmodules "On"
	warnings        "Off"
	
	defines {
		"GLM_ENABLE_EXPERIMENTAL", 
		
		"GLM_GTC_INLINE_NAMESPACE", 
		"GLM_EXT_INLINE_NAMESPACE", 
		"GLM_GTX_INLINE_NAMESPACE", 
	}
	
	includedirs {
		"%{prj.location}", 
	}	
	
	files {
		"%{prj.location}/glm/**.hpp", 
		"%{prj.location}/glm/**.cpp", 
		"%{prj.location}/glm/**.inl", 
		"%{prj.location}/glm/**.ixx", 
	}



	include "vendor/jolt"
	include "vendor/mimalloc"
	include "vendor/nlohmann"
	include "vendor/stb"
group ""



group "Application"
project "FOX"
	location         "fox"
	language         "C++"
	cppdialect       "C++23"
	kind             "StaticLib"
	staticruntime    "On"
	enablemodules    "On"
	buildstlmodules  "On"
	warnings         "Extra"
	externalwarnings "Off"
	
	defines {
		'FOX_ENGINE', 
		"FOX_MALLOC", 
		'FOX_ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
		
		"GLFW_INCLUDE_NONE", 
	}
	
	includedirs {
		"%{prj.name}/source", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.ENTT}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.JOLT}", 
		"%{includedir.MIMALLOC}", 
		"%{includedir.NLOHMANN}", 
		"%{includedir.STB}", 
	}
	
	files {
		"fox/source/**.hpp", 
		"fox/source/**.cpp", 
		"fox/source/**.ixx", 
	}
	
	links {
		"ASSIMP", 
		"ENTT", 
		"GLAD", 
		"GLFW", 
		"GLM", 
		"JOLT", 
		"MIMALLOC", 
		"NLOHMANN", 
		"STB", 
		
		"opengl32.lib", 
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"NOMINMAX", 
			"FOX_PLATFORM_WINDOWS", 
		}
	
	filter "configurations:Debug"
		defines   "FOX_DEBUG"
		
	filter "configurations:Release"
		defines   "FOX_RELEASE"



project "RUN"
	location         "run"
	language         "C++"
	cppdialect       "C++23"
	kind             "ConsoleApp"
	staticruntime    "On"
	enablemodules    "On"
	buildstlmodules  "On"
	warnings         "Extra"
	externalwarnings "Off"
	
	includedirs {
		"fox/source", 
	}
	
	files {
		"run/source/**.hpp", 
		"run/source/**.cpp", 
		"run/source/**.ixx", 
	}
	
	links {
		"FOX", 
	}
	
group ""
