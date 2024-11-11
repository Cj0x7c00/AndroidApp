#include "VulkanContext.h"
#include "Core/Window.h"
#include "Core/App.h"

namespace anv {
	VulkanContext::VulkanContext(Window* _win)
	{
		vkc_instance  (); // instance creation
		vkc_surface   (_win); // rendering surface
		//vkc_physical  (); // select gpu
		//vkc_logical   (); // create logical device
	}

	VulkanContext::~VulkanContext()
	{

	#ifdef DEBUG
		m_DebugInfo.DestroyDebugUtilsMessengerEXT(m_Instance, nullptr);
	#endif

		vkDestroyInstance(m_Instance, nullptr);
	}

	// == Privates

	void VulkanContext::vkc_instance()
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.apiVersion = VK_API_VERSION_1_0;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pApplicationName = "AndroidApp";
		appInfo.pEngineName = "AndroidApp";

		VkInstanceCreateInfo info{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pApplicationInfo = &appInfo,
		};

	// Get Required Extensions

		auto extensions = vkc_get_vk_extensions();
		
		info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		info.ppEnabledExtensionNames = extensions.data();

	// Validation Layers //

#ifdef DEBUG 
		if (!vkc_check_validation_support())
			throw std::runtime_error("Validation layers not supported!");

		info.enabledLayerCount = static_cast<uint32_t>(m_DebugInfo.Layers.size());
		info.ppEnabledLayerNames = m_DebugInfo.Layers.data();

		// Set up debug messenger create info
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
#ifdef DEBUGG

		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
#else
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
#endif
		debugCreateInfo.pfnUserCallback = VKCDebugInfo::debugCallback;

		info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#else
		info.enabledLayerCount = 0;
#endif // DEBUG

		VK_CHECK_RESULT(vkCreateInstance(&info, nullptr, &m_Instance), "Failed to create a vulkan instance!")

	// Validation Messenger
	#ifdef DEBUG
		VK_CHECK_RESULT(m_DebugInfo.CreateDebugUtilsMessengerEXT(m_Instance, &debugCreateInfo, nullptr), "Failed to create VK validation messenger!")
	#endif // DEBUG

	}

	_vec(const char*) VulkanContext::vkc_get_vk_extensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef DEBUG
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // DEBUG

		return extensions;
	}

#ifdef DEBUG
	bool VulkanContext::vkc_check_validation_support()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		_vec(VkLayerProperties) availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_DebugInfo.Layers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}
	}
#endif // DEBUG

	void VulkanContext::vkc_surface(Window* _win)
	{
		VK_CHECK_RESULT(glfwCreateWindowSurface(m_Instance, _win->m_WinPtr, nullptr, &m_Surface),
			"Failed to create a window surface!")
	}
}
