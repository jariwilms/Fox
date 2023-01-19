workspace "Helix"
	architecture "x64"
	startproject "Helix"
	
	configurations
	{
		"Debug", 
		"Release"
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["GLAD"] = "Helix/vendor/glad/include"
	includedir["GLFW"] = "Helix/vendor/glfw/include"
	includedir["STB"] = "Helix/vendor/stb/include"
	includedir["GLM"] = "Helix/vendor/glm/include"
	includedir["ENTT"] = "Helix/vendor/entt/include"
	includedir["TINYGLTF"] = "Helix/vendor/tinygltf/include"
	
	include "Helix/vendor/glad"
	include "Helix/vendor/glfw"
	include "Helix/vendor/tinygltf"
	
project "Helix"
	location "Helix"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "stdafx.hpp"
	pchsource "Helix/src/stdafx.cpp"
	
	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.STB}", 
		"%{includedir.GLM}", 
		"%{includedir.ENTT}", 
		"%{includedir.TINYGLTF}", 
	}
	
	links
	{
		"GLAD", 
		"GLFW", 
		"opengl32.lib"
	}
	
	defines
	{
		"STB_IMAGE_STATIC", 
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
		
		"TINYGLTF_IMPLEMENTATION", 
	}
	
	disablewarnings
	{
		"4250", 
		"26451", 
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HLX_PLATFORM_WINDOWS", 
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		runtime "Release"
		optimize "On"