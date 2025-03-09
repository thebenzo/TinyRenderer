workspace "TinyRenderer"
    architecture "x64"
    configurations 
    { 
        "Debug", 
        "Release" 
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TinyRenderer"
    location "TinyRenderer"
    kind "ConsoleApp"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.c" 
    }

    includedirs
    {
        "vendor/sdl2/include"
    }

    libdirs
    {
        "vendor/sdl2/lib/x64"
    }

    links
    {
        "SDL2",
        "SDL2main"
    }

    filter "system:windows"
        systemversion "latest"

        postbuildcommands
        {
            ("{COPYFILE} ../vendor/sdl2/lib/x64/SDL2.dll ../bin/" .. outputdir .. "/%{prj.name}")
        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
