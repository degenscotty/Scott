workspace "Scott"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Scott/vendor/imgui"

project "Scott"
	location "Scott"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "scpch.h"
	pchsource "Scott/src/scpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/imgui",
		"3rdParty/SDL2_ttf/include",
		"3rdParty/SDL2_image/include",
		"3rdParty/SDL2/include",
		"3rdParty/glm/glm"
	}
	
	libdirs
	{
		"3rdParty/SDL2_ttf/lib/x64",
		"3rdParty/SDL2_image/lib/x64",
		"3rdParty/SDL2/lib/x64"
	}
	
	links
	{
		"ImGui"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"SC_PLATFORM_WINDOWS",
			"SC_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "SC_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "SC_RELEASE"
		runtime "Release"
		symbols "On"
		
	filter "configurations:Dist"
		defines "SC_DIST"
		runtime "Release"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" 
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Scott/vendor/spdlog/include",
		"Scott/vendor/imgui",
		"Scott/src",
		"3rdParty/SDL2_ttf/include",
		"3rdParty/SDL2_image/include",
		"3rdParty/SDL2/include",
		"3rdParty/glm/glm"
	}
	
	libdirs
	{
		"3rdParty/SDL2_ttf/lib/x64",
		"3rdParty/SDL2_image/lib/x64",
		"3rdParty/SDL2/lib/x64"
	}
	
	links
	{
		"Scott"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"SC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SC_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "SC_RELEASE"
		runtime "Release"
		symbols "On"
		
	filter "configurations:Dist"
		defines "SC_DIST"
		runtime "Release"
		symbols "On"