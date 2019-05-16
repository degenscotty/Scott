#pragma once
#include "Scott/Layer.h"
#include "Scott/SceneGraph/SceneManager.h"


class GameLayer : public Scott::Layer
{
public:
	GameLayer();
	~GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void Render() override;

private:
	Scott::SceneManager& m_SceneManager;
};

