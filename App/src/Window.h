#pragma once
#include <GLFW/glfw3.h>

struct WindowSpec
{
	int width, height;
	const char* name;
};

class Window
{
public:
	Window(const WindowSpec& spec);
	~Window();

	void PollInput();
	bool ShouldClose();

private:
	GLFWwindow* m_WinPtr;
};

