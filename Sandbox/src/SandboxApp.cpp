#include "scpch.h"
#include <Scott.h>

class ExampleLayer : public Scott::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//SC_INFO("ExampleLayer::Update");
	}

	void OnEvent(Scott::Event& event) override
	{

	}
};



class Sandbox : public Scott::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Scott::Application* Scott::CreateApplication()
{
	return new Sandbox();
}