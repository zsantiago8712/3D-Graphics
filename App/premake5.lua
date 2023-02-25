project "3D-Graphics"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"


    links {"SDL2", "assimp", "Platform:shared"}
    includedirs { "../App/src", "../App/vendor/LA/src" }


    files {
        "main.cpp",
        "src/core/**.cpp",
        "src/render/**.cpp",
        "src/mesh/**.cpp",
    }




    filter { "system:windows" }
        system "windows"



    filter { "system:macosx", "system:linux" }
        system "macosx"



    buildoptions { 
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wnon-virtual-dtor",
        "-Wold-style-cast",
        "-Wcast-align",
        "-Wunused",
        "-Woverloaded-virtual",
        "-Wconversion",
        "-Wsign-conversion",
        "-Wmisleading-indentation",
        "-Wno-missing-braces"
    }


    filter { "configurations:Debug" }
        defines { "DEBUG" }
        targetdir("../bin/Debug/" .. outputdir .. "/%{prj.name}")
        objdir("../obj/Debug/" .. outputdir .. "/%{prj.name}")
        symbols "On"


    filter { "configurations:Release" }
        targetdir("../bin/Release/" .. outputdir .. "/%{prj.name}")
        objdir("../obj/Release/" .. outputdir .. "/%{prj.name}")
        symbols "Off"
        optimize "Full"