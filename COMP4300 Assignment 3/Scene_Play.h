#pragma once
#include "Scene.h"
#include "Entity.h"
#include "GameEngine.h"
#include "Vec2.h"
#include "Action.h"

class Scene_Play : public Scene
{
	struct playerConfig { int GX, GY; float MX, MY; };
	
	playerConfig	m_playerConfig{};
	EntityPtr		m_player{};

public:
	Scene_Play() {}

	Scene_Play(GameEngine* game, const std::string& levelPath)
		: Scene{ game }
	{
		init(levelPath);
	}

	Vec2 gridToMidPixel(const int gridX, const int gridY, EntityPtr entity);
	void loadLevel(const std::string& levelPath);
	void spawnFireball();
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
	void init(const std::string& levelPath);
};