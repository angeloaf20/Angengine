#include <Angengine/Window.h>

Window::Window(int width, int height, std::string title)
	: Width{ width }, Height{ height }, Title{ title }, m_IsRunning{ true }
{
	if (!glfwInit())
	{
		std::println("Could not initialize GLFW");
		return;
	}

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{

	}
}

Window::~Window()
{
	std::print("Destroying window");
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

GLFWwindow* Window::GetHandle() const
{
	return m_Window;
}

void Window::PollEvents()
{
	glfwPollEvents();
}

bool Window::IsWindowAndContextCreated()
{
	if (!m_Window)
	{
		std::println("Failed to create GLFW window");
		return false;
	}
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::println("Failed to initialize GLAD");
		return false;
	}

	return true;
}

bool Window::ShouldWindowClose() const
{
	return m_IsRunning;
}