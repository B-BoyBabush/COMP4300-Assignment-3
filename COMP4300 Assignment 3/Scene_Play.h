#pragma once
#include "Scene.h"
#include "Entity.h"
#include "GameEngine.h"
#include "Vec2.h"
#include "Action.h"

class Scene_Play : public Scene
{
	EntityPtr m_player{};

public:
	Scene_Play() {}

	Scene_Play(GameEngine* game)
		: Scene{ game }
	{}

	Vec2 gridToMidPixel(const int gridX, const int gridY, EntityPtr entity);
	void loadLevel();
	void spawnEnemy();
	void spawnPlayer();

	void sCollision();
	void sMovement();
	void sState();
	void sAnimate();
	void draw(EntityPtr entity);
	void sRender();

	virtual void sDoAction(const Action& action);
	virtual void registerActions();
	virtual void update();
	virtual void init();
};