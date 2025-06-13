project "MIMALLOC"
	language      "C++"
	cppdialect    "C++17"
	kind          "StaticLib"
	staticruntime "On"
	
	defines 
	{
		"WIN32", 
		"_WINDOWS", 
		
		"MI_STATIC_LIB", 
	}
	
	includedirs 
	{
		"include", 
		"include/mimalloc", 
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
	
	disablewarnings
	{
		28251, 
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
