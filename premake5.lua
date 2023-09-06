include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Needles"
	architecture "x86_64"
	startproject "Needles" -- This will be changed to PINS later after NEEDLES is nearing completion

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
group ""

group "Core"
	include "Needles"
group ""