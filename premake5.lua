require "ninja"

workspace "Fractales"
    architecture "x64"
    configurations { "Debug", "Release" }
    location "build"

project "Fractales"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/*.cpp", "main.cpp"}
    includedirs { "include",  "src/Headers" } 
    libdirs { "lib" }
    links { "glfw3dll" }
    defines { "GLFW_INCLUDE_NONE" }

    filter "configurations:Debug"
        cppdialect "C++20"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "DEBUG" }
        optimize "On"