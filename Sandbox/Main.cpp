#include <iostream>
#include <exception>
#include <stdio.h>

#include "Core\Engine.h"
#include "Core\SEngineContext.h"
#include "Utilities\Utilities.h"

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