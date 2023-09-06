project "Needles"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ndlpch.h"
	pchsource "src/ndlpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		}

	filter "configurations:Debug"
		defines "NDL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NDL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NDL_DIST"
		runtime "Release"
		optimize "on"
