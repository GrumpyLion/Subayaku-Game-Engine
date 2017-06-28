#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Core\Engine.h"
#include "Core\SEngineContext.h"

int main()
{	
	//break at the point the memory which is not freed is allocated, is told by _CrtDumpMemoryLeaks
	//_CrtSetBreakAlloc(2174);

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

	}

	//Add at the end to see which memory leaks still exist,
	//will output all unfreed memories
	_CrtDumpMemoryLeaks();

	return 0;
}