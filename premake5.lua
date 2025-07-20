workspace "Fox Engine"
	startproject "RUN"
	architecture "x64"
	
	configurations { 
		"Debug", 
		"Release", 
	}
	includedir = {
		["ASSIMP"  ] = "vendor/assimp/include", 
		["ENTT"    ] = "vendor/entt/single_include", 
		["GLAD"    ] = "vendor/glad/include", 
		["GLFW"    ] = "vendor/glfw/include", 
		["GLM"     ] = "vendor/glm", 
		["JOLT"    ] = "vendor/jolt/include", 
		["MIMALLOC"] = "vendor/mimalloc/include", 
		["NLOHMANN"] = "vendor/nlohmann/include", 
		["STB"     ] = "vendor/stb", 
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
		"fox/source", 
		
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
		
		"ASSIMP", 
		"ENTT", 
		"GLAD", 
		"GLFW", 
		"GLM", 
		"JOLT", 
		"MIMALLOC", 
		"NLOHMANN", 
		"STB", 
	}
group ""
