#include <iostream>

#include "Core\Engine.h"
#include "Core\SEngineContext.h"
#include "Utilities\Utilities.h"

int main()
{	
	auto engine = std::make_unique<Core::Engine>();
	Core::SEngineContext context{};
	context.RDevice = Core::RenderDevice::OpenGL;
	context.Width = 1360;
	context.Height = 850;

	//Check for errors while init
	if (engine->Initialize(context))
	{
		engine->Run();
	}
	
	return 0;
}