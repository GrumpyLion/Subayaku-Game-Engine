#pragma once

#include "Engine.h"

#include "Utilities\Utilities.h"

//Structs
#include "SEngineContext.h"
#include "Graphics\Interface\SRendererDesc.h"

//Maths
#include "Math\Math.h"

//Renderers
#include "Graphics\Interface\IRenderer.h"
#include "Graphics\OpenGL\GLRenderer.h"
#include "Graphics\DirectX\D3DRenderer.h"

//Caches
#include "Graphics\Interface\IRenderFactory.h"
#include "Graphics\OpenGL\GLRenderFactory.h"
#include "Graphics\DirectX\D3DRenderFactory.h"
#include "Utilities\Cache.h"
#include <GrumpyZip\ZipFile.h>

//IO
#include "Window\Interface\IWindow.h"
#include "Window\Window.h"
#include "Input\Keyboard.h"
#include "Input\InputManager.h"

//Scene
#include "Scene\Scene.h"
#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Interface\IComponent.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Scene\GameObject\Components\CCamera.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"