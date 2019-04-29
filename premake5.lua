workspace "Scott"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Scott"
	location "Scott"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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
		symbols "On"
		
	filter "configurations:Release"
		defines "SC_RELEASE"
		symbols "On"
		
	filter "configurations:Dist"
		defines "SC_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" 
	language "C++"
	
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
		"Scott/src"
	}

	links
	{
		"Scott"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"SC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SC_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SC_RELEASE"
		symbols "On"
		
	filter "configurations:Dist"
		defines "SC_DIST"
		symbols "On"