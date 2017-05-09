#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

#include "IComponent.h"

class CCamera : public IComponent {

	public:
		~CCamera()
		{
			printf("CCamera Deleted\n");
		}

		void Update() override
		{
			printf("CCamera\n");
		}
};

class CMeshRenderer : public IComponent {

public:
	~CMeshRenderer()
	{
		printf("CMesh Deleted\n");
	}

	void Update() override
	{
		printf("CMeshrenderer\n");
	}
};

int main(void)
{
	std::vector<std::unique_ptr<IComponent>> tests;

	auto test = std::make_unique<CCamera>();

	tests.push_back(std::move(test));
	tests.push_back(std::make_unique<CMeshRenderer>());

	for (auto &temp : tests)
	{
		temp->Update();
	}
}