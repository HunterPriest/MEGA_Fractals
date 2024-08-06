require "vendor/premake-ninja/ninja"

workspace "Fractals"
    configurations { "Debug", "Release" }
    system ( "Windows" )
    location "build"
    architecture "x64"
    include "vendor/glfw.lua"

project "Fractals"
    language "C++"
    cppdialect "C++20"
    toolset "Clang"

    files
    {
     "src/*.cpp",
     "src/Core/*.cpp",
     "src/Gui/*.cpp",
     "src/Fractals/*.cpp",
     "vendor/imgui/backends/imgui_impl_opengl3.cpp",
     "vendor/imgui/backends/imgui_impl_glfw.cpp",
     "vendor/imgui/*.cpp",
     "vendor/glad/glad/glad.cpp", 
     "src/Tools/*.cpp", 
     "src/Figure/*.cpp"
    }

    includedirs 
    {
     "src/Core",
     "src/Gui",
     "src/Fractals",
     "vendor/glad", 
     "vendor/glfw/include", 
     "vendor/glm",
     "vendor/imgui/backends", 
     "vendor/imgui",
     "vendor/nlohmann/include", 
     "src/Tools", 
     "src/Figure"
    } 

    links { "GLFW" }
    defines { "GLFW_INCLUDE_NONE", "_USE_MATH_DEFINES" }

    filter "system:Windows"
        links { "user32", "gdi32", "shell32" }

    filter "configurations:Debug"
        kind "ConsoleApp"
        runtime "Debug"
        defines { "DEBUG" }
        symbols "On"
        linkoptions { "-fuse-ld=lld -g -Wl" }
        targetdir "build/Debug/bin"
        objdir  "build/obj/Debug"
        libdirs { "build/Debug/GLFW" }

    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        targetdir "build/Release/bin"
        objdir  "build/obj/Release"
        libdirs { "build/Release/GLFW" }