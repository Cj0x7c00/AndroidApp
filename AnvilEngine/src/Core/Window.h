#pragma once

/**
* Note:
* OS window abstraction will happen within glfw.
* idc about OS window abstraction. i care about
* Graphics API abstraction and modularity.
**/

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

		Context* GetContext();

	private:
		GLFWwindow* m_WinPtr = nullptr;
		Context* m_Context   = nullptr;
		
		friend class VulkanContext;
	};

}