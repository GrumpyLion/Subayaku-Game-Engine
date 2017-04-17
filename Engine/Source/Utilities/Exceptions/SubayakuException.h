#pragma once

#include <exception>

class SubayakuException
{
public:
	const char* Message = "ERROR";
	virtual const char* what() const throw()
	{
		return Message;
	}
} SubayakuEx;