#include <Angengine/Angengine.hpp>

Angengine::Angengine()
	: m_Window{ 1280, 720, "Hello Angengine" }
{ }

Angengine::~Angengine()
{
	Cleanup();
}

void Angengine::Run()
{
	if (!m_Window.IsWindowAndContextCreated())
	{
		std::println("Closing engine");
		return;
	}

	while (!glfwWindowShouldClose(m_Window.GetHandle()))
	{
		m_Window.PollEvents();


	}
}

void Angengine::Cleanup()
{
	
}
