#include "scpch.h"
#include "GameObject.h"

namespace Scott
{
	GameObject::GameObject(const std::string& name)
		: m_Name( name )
	{

	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Update() 
	{
	}

	void GameObject::Render() const
	{
	}

	void GameObject::SetPosition(float x, float y)
	{	
	}
}
