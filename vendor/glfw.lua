require "premake-ninja/ninja"

project "GLFW"

	kind "StaticLib"
	language "C"
	staticruntime "on"
	systemversion "latest"

	files
	{
		"glfw/include/GLFW/glfw3.h",
    	"glfw/include/GLFW/glfw3native.h",
    	"glfw/src/internal.h",
    	"glfw/src/platform.h",
    	"glfw/src/mappings.h",
    	"glfw/src/context.c",
    	"glfw/src/init.c",
    	"glfw/src/input.c",
    	"glfw/src/monitor.c",
    	"glfw/src/platform.c",
    	"glfw/src/vulkan.c",
    	"glfw/src/window.c",
    	"glfw/src/egl_context.c",
    	"glfw/src/osmesa_context.c",
    	"glfw/src/null_platform.h",
    	"glfw/src/null_joystick.h",
    	"glfw/src/null_init.c",
    	"glfw/src/null_monitor.c",
    	"glfw/src/null_window.c",
    	"glfw/src/null_joystick.c",
	}

	filter "system:Windows"
		files
		{
			"glfw/src/win32_init.c",
			"glfw/src/win32_module.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_time.h",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.h",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}
			
		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}	

	filter "configurations:Debug"
		symbols "on"
		targetdir ("../build/Debug/%{prj.name}")
		objdir ("../build/obj/Debug/%{prj.name}")
		linkoptions { "-fuse-ld=lld -g -Wl" }

	filter "configurations:Release"
		targetdir ("../build/Release/%{prj.name}")
		objdir ("../build/obj/Debug/%{prj.name}")
		optimize "Speed"