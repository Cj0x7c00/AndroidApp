workspace "AndroidApp"

    architecture "x64"
    startproject "App" 
    

    configurations 
    {
        "Debug",
        "Release"
    }

--    VULKAN_SDK = os.getenv("VULKAN_SDK")
--    print("Vulkan SDK: ", VULKAN_SDK)
      outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
--    root_dir = os.getcwd() .. "/"
--    print("Root Directory: ", root_dir)
--    vendor_dir = root_dir .. "Anvil/include/"
--    print("Vendor Directory: ", vendor_dir)

    group "Dependencies"
        include "GLFW/glfw.lua"
        include "raylib/ray.lua"
    group ""

    group "App"
        include "App.lua"
    group ""