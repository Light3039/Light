project "Engine"

	-- Output Directories --
	location "%{wks.location}/Engine/"

	targetdir ("%{wks.location}/bin/"     .. outputdir)
	objdir    ("%{wks.location}/bin-int/" .. outputdir)

	-- Compiler --
	-- kind
	kind "StaticLib"

	-- language
	language "C++"
	cppdialect "C++17"

	-- pch
	pchsource "src/Engine/ltpch.cpp"
	pchheader "ltpch.h"

	-- Project Files ---
	files
	{
		"%{prj.location}/src/**.h"      ,
		"%{prj.location}/src/**.cpp"    ,
		"%{prj.location}/**.lua"        ,
		"%{prj.location}/dxgidebug.dll" ,
	}
	
	-- Dependencies --
	includedirs
	{
		-- engine
		"%{prj.location}/src"                     ,
		"%{prj.location}/src/Engine"              ,
		"%{prj.location}/src/Platform/GraphicsAPI" ,
		"%{prj.location}/src/Platform/OS"          ,

		-- 3rd party
		(dependenciesdir .. "spdlog/include/"),
		(dependenciesdir .. "GLFW/include/"  ),
		(dependenciesdir .. "GLAD/include"   ),
		(dependenciesdir .. "imgui/backends" ),
		(dependenciesdir .. "imgui/"         ),
		(dependenciesdir .. "glm/"           ),
	}

	links
	{
		"GLFW"  ,
		"GLAD"  ,
		"ImGui" ,
	}
	
	--- Filters ---
	-- windows
	filter "system:windows"
		defines "LIGHT_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "on"
		
		filter "files:%{prj.location}/src/Platform/OS/Linux/**"
			flags "ExcludeFromBuild"	
		filter "files:%{prj.location}/src/Platform/OS/Mac/**"
			flags "ExcludeFromBuild"	
		
		links
		{
			"d3d11.lib"       ,
			"dxguid.lib"      ,
			"D3DCompiler.lib" ,
		}
	
	-- linux
	filter "system:linux"
		defines "LIGHT_PLATFORM_LINUX"
		links
		{
			"dl",
		}
		
		buildoptions
		{
			"-lgtest",
			"-lpthread",
		}
		
		filter "files:src/Platform/GraphicsAPI/DirectX/**.**"
			flags "ExcludeFromBuild"
		filter "files:src/Platform/OS/Windows/**.**"
			flags "ExcludeFromBuild"

	-- debug
	filter "configurations:Debug"
		defines "LIGHT_DEBUG"
		symbols "on"

	-- release
	filter "configurations:Release"
		defines "LIGHT_RELEASE"
		optimize "on"

	-- distribution
	filter "configurations:Distribution"
		defines "LIGHT_DIST"
		optimize "on"

	--- Excludes ---
	-- !windows
	filter "system:not linux"

	-- !linux #todo:
	-- !mac #todo: