#pragma once

#include "Engine.h"


//Structs
#include "SEngineContext.h"
#include "Graphics\Descriptions\SRendererDesc.h"

//Maths
#include "Math\Math.h"

//Renderers
#include "Graphics\Interfaces\IRenderer.h"

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