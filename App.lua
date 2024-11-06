project "App"
        location "App"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        warnings "off"

        targetdir("bin/" .. outdir .. "/%{prj.name}")
        objdir( "bin-int/" .. outdir .. "/%{prj.name}")

      

        defines
        {

        }

        print("Install Dir: ", INSTALL_DIR)

        files
        {
            "App/**.cpp",
            "App/**.h"
        }

        includedirs
        {
            "GLFW/include",
        }

        libdirs 
        {
            "include/glfw/".. outdir .."/GLFW"
        }

        links
        {
            "GLFW"
        }


        buildoptions { "/MP" }

        filter "configurations:Debug"
            defines "DEBUG"
            optimize "on"
            linkoptions { "/SUBSYSTEM:CONSOLE" }
            kind "ConsoleApp"

        filter "configurations:Release"
            defines "RELEASE"
            optimize "on"
            linkoptions { "/SUBSYSTEM:WINDOWS" }
            kind "ConsoleApp"
