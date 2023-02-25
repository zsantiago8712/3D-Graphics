project "Platform"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"

    links { "SDL2" }
    files { "**.cpp" }



    filter  "configurations:Debug"
        defines { "DEBUG" }
        targetdir("../../../bin-libs/")
        objdir("../../../obj-libs/%{prj.name}")
        symbols "On"
        
        
    filter { "configurations:Release" }
        defines { "RELEASE" }
        targetdir("../../../bin-libs/")
        objdir("../../../obj-libs/%{prj.name}")

        symbols "Off"
        optimize "Full"