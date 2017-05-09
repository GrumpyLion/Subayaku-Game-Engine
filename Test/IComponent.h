#pragma once

class IComponent 
{
public:
	// Pure virtual function
	virtual ~IComponent() {}
	virtual void Update() = 0;
};
