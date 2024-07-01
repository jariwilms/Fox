workspace "Fox"
	architecture "x64"
	startproject "Fox"
	
	configurations
	{
		"Debug", 
		"Release"
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["GLAD"] = "Fox/vendor/glad/include"
	includedir["GLFW"] = "Fox/vendor/glfw/include"
	includedir["GLM"]  = "Fox/vendor/glm/include"
	includedir["STB"]  = "Fox/vendor/stb/include"
	includedir["ENTT"] = "Fox/vendor/entt/include"
	
	include "Fox/vendor/glad"
	include "Fox/vendor/glfw"
	
project "Fox"
	location "Fox"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "stdafx.hpp"
	pchsource "Fox/src/stdafx.cpp"
	
	files
	{
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.STB}", 
		"%{includedir.ENTT}", 
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"GLAD", 
		"GLFW", 
	
		
		"opengl32.lib", 
	}
	
	defines
	{
		"FOX_PLATFORM_WINDOWS", 
		"GLFW_INCLUDE_NONE", 
		"STB_IMAGE_STATIC", 
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
		"NOMINMAX", 		
		'PROJECT_DIR=R"($(ProjectDir).)"', 
		'ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
	}
	
	disablewarnings
	{
		" 4250", --Buffer Dominance
		" 6262", --STB stack 
		"26451", --STB overflow
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FOX_PLATFORM_WINDOWS", 
			"NOMINMAX", 
		}
		
	filter "configurations:Debug"
		defines "FOX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "FOX_RELEASE"
		runtime "Release"
		optimize "On"
