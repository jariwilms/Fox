project "MIMALLOC"
	language      "C++"
	cppdialect    "C++17"
	kind          "StaticLib"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/obj")

	defines 
	{
		"WIN32", 
		"_WINDOWS", 
		
		"MI_STATIC_LIB", 
	}

	files 
	{
		"src/alloc.c", 
		"src/alloc-aligned.c", 
		"src/alloc-posix.c", 
		"src/arena.c", 
		"src/bitmap.c", 
		"src/heap.c", 
		"src/init.c", 
		"src/libc.c", 
		"src/options.c", 
		"src/os.c", 
		"src/page.c", 
		"src/prim/prim.c", 
		"src/random.c", 
		"src/segment.c", 
		"src/segment-map.c", 
		"src/stats.c", 
	}

	includedirs 
	{
		"include", 
		"include/mimalloc", 
	}

	disablewarnings
	{
		28251, 
	}

	filter "system:windows"
		systemversion "latest"

	filter  "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter  "configurations:Release"
		runtime "Release"
		optimize "On"
