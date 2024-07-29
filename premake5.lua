require "ninja"

workspace "Fractales"
    architecture "x64"
    configurations { "Debug", "Release" }
    location "build"

project "Fractales"
    symbols "On"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/*.cpp", "src/Core/*.cpp" , "src/Gui/*.cpp" , "src/imgui/*.cpp", "src/Fractals/*.cpp" }
    includedirs { "include",  "src/Headers", "include/imgui", "src/Core", "src/Gui", "src/Fractals" } 
    libdirs { "lib" }
    links { "glfw3dll" }
    defines { "GLFW_INCLUDE_NONE" }

    filter "configurations:Debug"
        cppdialect "C++20"
        defines { "DEBUG" }
        symbols "On"
        linkoptions { "-fuse-ld=lld -g -Wl" }

    filter "configurations:Release"
        defines { "Release" }
        optimize "On"