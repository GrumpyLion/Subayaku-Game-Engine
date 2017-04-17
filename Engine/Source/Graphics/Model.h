#pragma once

#include <vector>

namespace Graphics 
{
	class Mesh;
	
	class Model 
	{
		std::vector<Mesh*> m_Meshes;
	};

}