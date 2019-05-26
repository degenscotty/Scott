#include "scpch.h"
#include <Scott.h>
#include "Layers/GameLayer.h"

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
};



class Sandbox : public Scott::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{
	}
};

Scott::Application* Scott::CreateApplication()
{
	return new Sandbox();
}