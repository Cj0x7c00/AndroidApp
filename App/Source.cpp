#include <GLFW/glfw3.h>
#include <stdexcept>

int main()
{
	if (!glfwInit())
	{
		throw std::runtime_error("failed to init glfw");
	}

	GLFWwindow* window = glfwCreateWindow(700, 500, "Bitch ass nigga", NULL, NULL);

	if (!window)
	{
		std::runtime_error("Failed to create window");
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}