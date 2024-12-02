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
	includedir["GLAD"]     = "Fox/vendor/glad/include"
	includedir["GLFW"]     = "Fox/vendor/glfw/include"
	includedir["GLM"]      = "Fox/vendor/glm/include"
	includedir["STB"]      = "Fox/vendor/stb/include"
	includedir["ENTT"]     = "Fox/vendor/entt/include"
	includedir["TINYGLTF"] = "Fox/vendor/tinygltf/include"
	
	include "Fox/vendor/glad"
	include "Fox/vendor/glfw"
	include "Fox/vendor/stb"
	include "Fox/vendor/tinygltf"
	
project "Fox"
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
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp", 
		
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.STB}", 
		"%{includedir.ENTT}", 
		"%{includedir.TINYGLTF}", 
	}
	
	libdirs
	{
		
	}
	
	links
	{
		"GLAD", 
		"GLFW", 
		"STB_IMAGE", 
		
		"opengl32.lib", 
	}
	
	defines
	{
		'PROJECT_DIR=R"($(ProjectDir).)"', 
		'ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
	
		"GLFW_INCLUDE_NONE", 
		
		"TINYGLTF_IMPLEMENTATION", 
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
