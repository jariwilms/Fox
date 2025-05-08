workspace "Fox"
	architecture "x64"
	startproject "RUN"
	
	configurations
	{
		"Debug", 
		"Release", 
	}
	
	includedir = {}
	includedir["ASSIMP"]   = "Fox/vendor/assimp/include"
	includedir["ENTT"]     = "Fox/vendor/entt/include"
	includedir["GLAD"]     = "Fox/vendor/glad/include"
	includedir["GLFW"]     = "Fox/vendor/glfw/include"
	includedir["GLM"]      = "Fox/vendor/glm/include"
	includedir["MIMALLOC"] = "Fox/vendor/mimalloc/include"
	includedir["STB"]      = "Fox/vendor/stb/include"
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
group "Dependencies"
	include "Fox/vendor/assimp"
	include "Fox/vendor/entt"
	include "Fox/vendor/glad"
	include "Fox/vendor/glfw"
	include "Fox/vendor/glm"
	include "Fox/vendor/mimalloc"
	include "Fox/vendor/stb"
group ""

group "Application"
project "FOX"
	location      "FOX"
	language      "C++"
	cppdialect    "C++20"
	kind          "StaticLib"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")
	
	pchheader "stdafx.hpp"
	pchsource "Fox/src/stdafx.cpp"
	
	defines
	{
		'FOX_PROJECT_DIR=R"($(ProjectDir).)"', 
		'FOX_ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
		"FOX_MALLOC", 
		
		"GLFW_INCLUDE_NONE", 
		"GLM_ENABLE_EXPERIMENTAL", 
	}
	
	files
	{
		"Fox/src/**.hpp", 
		"Fox/src/**.cpp", 
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.ENTT}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
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
	cppdialect    "C++20"
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
		"Run/src/**.hpp", 
		"Run/src/**.cpp", 
	}
	
	includedirs
	{
		"Fox/src", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.ENTT}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
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
