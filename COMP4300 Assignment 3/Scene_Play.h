#pragma once
#include "Scene.h"
#include "Action.h"

class Scene_Play : public Scene
{
	EntityPtr m_player{};

public:
	Scene_Play() {}

	Scene_Play(GameEngine* game)
		: Scene{ game }
	{}

	Vec2 gridToMidPixel(const int gridX, const int gridY);
	void loadLevel();
	void spawnEnemy();
	void spawnPlayer();

	void sMovement();
	void sAnimate();
	void sRender();

	virtual void sDoAction(const Action& action);
	virtual void registerActions();
	virtual void update();
	virtual void init();
};