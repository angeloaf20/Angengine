#include <string>
#include <print>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;
	bool m_IsRunning;

public:
	int Width;
	int Height;
	std::string Title;

	Window(int width = 800, int height = 600, std::string title = "Angengine Window");
	~Window();
	void PollEvents();
	GLFWwindow* GetHandle() const;
	bool IsWindowAndContextCreated();
	bool ShouldWindowClose() const;
};