project "stb_image"

	location "%{wks.location}/Dependencies/stb_image"

	-- Output Directories --
	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	kind "StaticLib"
	language "C"
	
	optimize "on"

	-- Project Files ---
	files
	{
		"stb_image.c",
		"stb_image.h",

		"build.lua"
	}
	
	--- Filters ---
	-- windows
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS",
		}

		flags { "MultiProcessorCompile" }