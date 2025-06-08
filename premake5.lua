workspace "Fox"
	architecture "x64"
	startproject "RUN"
	
	configurations
	{
		"Debug", 
		"Release", 
	}
	
	includedir = 
	{
		["ASSIMP"]   = "Fox/vendor/assimp/include", 
		["ENTT"]     = "Fox/vendor/entt/include", 
		["GLAD"]     = "Fox/vendor/glad/include", 
		["GLFW"]     = "Fox/vendor/glfw/include", 
		["GLM"]      = "Fox/vendor/glm/include", 
		["NLOHMANN"] = "Fox/vendor/nlohmann/include", 
		["MIMALLOC"] = "Fox/vendor/mimalloc/include", 
		["STB"]      = "Fox/vendor/stb/include", 
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
group "Dependencies"
	include "Fox/vendor/assimp"
	include "Fox/vendor/entt"
	include "Fox/vendor/glad"
	include "Fox/vendor/glfw"
	include "Fox/vendor/glm"
	include "Fox/vendor/nlohmann"
	include "Fox/vendor/mimalloc"
	include "Fox/vendor/stb"
group ""

group "Application"
project "FOX"
	location      "FOX"
	language      "C++"
	cppdialect    "C++23"
	kind          "StaticLib"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")
	
	pchheader "stdafx.hpp"
	pchsource "Fox/source/stdafx.cpp"
	
	defines
	{
		'FOX_ENGINE', 
		'FOX_PROJECT_DIR=R"($(ProjectDir).)"', 
		'FOX_ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
		"FOX_MALLOC", 
		
		"GLFW_INCLUDE_NONE", 
		"GLM_ENABLE_EXPERIMENTAL", 
	}
	
	files
	{
		"Fox/source/**.hpp", 
		"Fox/source/**.cpp", 
	}
	
	includedirs
	{
		"%{prj.name}/source", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.ENTT}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.NLOHMANN}", 
		"%{includedir.MIMALLOC}", 
		"%{includedir.STB}", 
	}
	
	links
	{
		"ASSIMP", 
		"ENTT", 
		"GLAD", 
		"GLFW", 
		"GLM", 
		"NLOHMANN", 
		"MIMALLOC", 
		"STB_IMAGE", 
		
		"opengl32.lib", 
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NOMINMAX", 
			
			"FOX_PLATFORM_WINDOWS", 
		}
		
	filter "configurations:Debug"
		defines "FOX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines  "FOX_RELEASE"
		runtime  "Release"
		optimize "On"



project "RUN"
	location      "RUN"
	language      "C++"
	cppdialect    "C++23"
	kind          "ConsoleApp"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")
	
	defines
	{
		"GLFW_INCLUDE_NONE", 
		"GLM_ENABLE_EXPERIMENTAL", 
	}
	
	files
	{
		"Run/source/**.hpp", 
		"Run/source/**.cpp", 
	}
	
	includedirs
	{
		"Fox/source", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.ENTT}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.NLOHMANN}", 
		"%{includedir.STB}", 
	}
	
	links
	{
		"FOX", 
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime  "Release"
		optimize "On"
group ""
