workspace "Fox"
	architecture "x64"
	startproject "FOX"
	
	configurations
	{
		"Debug", 
		"Release", 
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["ASSIMP"]   = "Fox/vendor/assimp/include"
	includedir["ENTT"]     = "Fox/vendor/entt/include"
	includedir["GLAD"]     = "Fox/vendor/glad/include"
	includedir["GLFW"]     = "Fox/vendor/glfw/include"
	includedir["GLM"]      = "Fox/vendor/glm/include"
	includedir["STB"]      = "Fox/vendor/stb/include"
	includedir["TINYGLTF"] = "Fox/vendor/tinygltf/include"
	
	include "Fox/vendor/assimp"
	include "Fox/vendor/entt"
	include "Fox/vendor/glad"
	include "Fox/vendor/glfw"
	include "Fox/vendor/stb"
	include "Fox/vendor/tinygltf"
	
project "FOX"
	location "Fox"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/"  .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "stdafx.hpp"
	pchsource "Fox/src/stdafx.cpp"
	
	files
	{
		"Fox/src/**.hpp", 
		"Fox/src/**.h", 
		
		"Fox/src/**.cpp", 
		"Fox/src/**.c", 
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		
		"%{includedir.ASSIMP}", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.STB}", 
		"%{includedir.ENTT}", 
		"%{includedir.TINYGLTF}", 
	}
	
	links
	{
		"ASSIMP", 
		"ENTT", 
		"GLAD", 
		"GLFW", 
		"STB_IMAGE", 
		"TINYGLTF", 
		
		"opengl32.lib", 
	}
	
	defines
	{
		'PROJECT_DIR=R"($(ProjectDir).)"', 
		'ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
		
		"GLFW_INCLUDE_NONE", 
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
		defines "FOX_RELEASE"
		runtime "Release"
		optimize "On"
