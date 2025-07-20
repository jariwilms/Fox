workspace "fox-engine"
	startproject "run"
	architecture "x64"
	
	configurations { 
		"Debug", 
		"Release", 
	}
	includedir = {
		["assimp"  ] = "vendor/assimp/include", 
		["entt"    ] = "vendor/entt/single_include", 
		["glad"    ] = "vendor/glad/include", 
		["glfw"    ] = "vendor/glfw/include", 
		["glm"     ] = "vendor/glm/include", 
		["jolt"    ] = "vendor/jolt/include", 
		["mimalloc"] = "vendor/mimalloc/include", 
		["nlohmann"] = "vendor/nlohmann/include", 
		["stb"     ] = "vendor/stb/include", 
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
		
		if premake.project.iscpp(prj) and string.find(prj.filename, "fox") then
			table.insertafter(calls, premake.xmlDeclaration,  function()
				premake.w('<ModuleDependenciesFile>$(IntDir)\\%%(RelativeDir)</ModuleDependenciesFile>')
				premake.w('<ModuleOutputFile>$(IntDir)\\%%(RelativeDir)</ModuleOutputFile>')
				premake.w('<ObjectFileName>$(IntDir)\\%%(RelativeDir)</ObjectFileName>')
			end)
		end

		return calls
	end)



group "Application"
	project "fox"
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
			"fox/source", 
			
			"%{includedir.assimp}", 
			"%{includedir.entt}", 
			"%{includedir.glad}", 
			"%{includedir.glfw}", 
			"%{includedir.glm}", 
			"%{includedir.jolt}", 
			"%{includedir.mimalloc}", 
			"%{includedir.nlohmann}", 
			"%{includedir.stb}", 
		}
		files {
			"fox/source/**.hpp", 
			"fox/source/**.cpp", 
			"fox/source/**.ixx", 
		}
		links {
			"assimp", 
			"entt", 
			"glad", 
			"glfw", 
			"glm", 
			"jolt", 
			"mimalloc", 
			"nlohmann", 
			"stb", 
			
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



	project "run"
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
			"fox", 
		}



group "Dependencies"
	include "vendor/assimp"
	include "vendor/entt"
	include "vendor/glad"
	include "vendor/glfw"
	include "vendor/glm"
	include "vendor/jolt"
	include "vendor/mimalloc"
	include "vendor/nlohmann"
	include "vendor/stb"
group ""