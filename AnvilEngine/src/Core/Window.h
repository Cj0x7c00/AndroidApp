#pragma once
#include "../Render/Context/Context.h"

#include <string>

struct GLFWwindow;

namespace anv {


	struct WindowCreateInfo
	{
		int width, height;
		std::string name = "Anvil App Window";
	};

	class Window
	{
	public:
		Window(WindowCreateInfo _info);
		~Window();

		void OnUpdate();
		bool ShouldClose();

	private:
		GLFWwindow* m_WinPtr = nullptr;
		Context* m_Context   = nullptr;
		
		friend class VulkanContext;
	};

}