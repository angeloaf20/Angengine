#ifndef ANGENGINE_H
#define ANGENGINE_H

#include <Angengine/Window.hpp>

class Angengine
{
private:
	std::unique_ptr<Window> m_Window;
	void Cleanup();

public:
	Angengine();
	~Angengine();
	void Run();
	
};

#endif // ANGENGINE_H