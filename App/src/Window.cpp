#include "Window.h"

#include <stdexcept>

Window::Window(const WindowSpec& spec)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to init GLFW!");
	}

	m_WinPtr = glfwCreateWindow(spec.width, spec.height, spec.name, NULL, NULL);
}

Window::~Window()
{
	glfwDestroyWindow(m_WinPtr);
	glfwTerminate();
}

void Window::PollInput()
{
	glfwPollEvents();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_WinPtr);
}

