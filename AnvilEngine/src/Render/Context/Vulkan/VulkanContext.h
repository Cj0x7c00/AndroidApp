#pragma once

#include "../Context.h"
#include "Util/UMacros.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>

#define VK_CHECK_RESULT(f, msg) {                                                                \
    VkResult res = (f);                                                                          \
    if (res != VK_SUCCESS) {                                                                     \
        throw std::runtime_error(                                                                \
            std::string("Vulkan Error: ") + std::to_string(res) +                                \
            "\nFile: " + __FILE__ +                                                              \
            "\nFunction: " + __FUNCTION__ +                                                      \
            "\nLine: " + std::to_string(__LINE__) +                                              \
            std::string(" : ") + std::string(msg));                                              \
    }                                                                                            \
    else                                                                                         \
    {                                                                                            \
        std::cout << "[" << __FUNCTION__ << "] >> VK CHECK RESULT PASSED\n";                     \
    }                                                                                            \
}                                                                                                \

namespace anv {

    struct VKCDebugInfo
    {
        VkDebugUtilsMessengerEXT debugMessenger;

        _vec(const char*) Layers = {
            "VK_LAYER_KHRONOS_validation",
        };

        inline static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

            std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
            return VK_FALSE;
        }

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            return func ? func(instance, pCreateInfo, pAllocator, &debugMessenger) : VK_ERROR_EXTENSION_NOT_PRESENT;
        }

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func) func(instance, debugMessenger, pAllocator);
        }
    };

    class VulkanContext
        : public Context
    {
    public:
        VulkanContext(Window* _win);
        ~VulkanContext();

    private:
        void vkc_instance(); // instance creation
        _vec(const char*) 
            vkc_get_vk_extensions();
        void vkc_surface(Window* _win); // rendering surface
        //void vkc_physical(); // select gpu
        //void vkc_logical(); // create logical device

#ifdef DEBUG
        bool vkc_check_validation_support();
#endif // DEBUG

    private:

        VkInstance m_Instance;
        VkSurfaceKHR m_Surface;
        VkDevice m_Device;
        VkPhysicalDevice m_PhysicalDevice;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;
        

    #ifdef DEBUG
        VKCDebugInfo m_DebugInfo;
    #endif // DEBUG
    };
}