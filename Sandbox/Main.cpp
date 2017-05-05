#include <iostream>

#include "Core\Engine.h"
#include "Core\SEngineContext.h"

int main()
{
	Core::Engine engine = Core::Engine();
	Core::SEngineContext context{};
	context.RDevice = Core::RenderDevice::OpenGL;

	//Check for errors while init
	if (engine.Initialize(context))
	{
		engine.Run();
	}
	
	return 0;
}