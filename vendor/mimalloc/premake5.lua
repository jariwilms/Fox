project "MIMALLOC"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
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
