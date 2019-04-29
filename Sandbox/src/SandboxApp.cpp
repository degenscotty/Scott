#include "scpch.h"
#include <Scott.h>

class Sandbox : public Scott::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

Scott::Application* Scott::CreateApplication()
{
	return new Sandbox();
}