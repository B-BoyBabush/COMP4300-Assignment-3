#pragma once

#include "Scene.h"
#include "GameEngine.h"

class Scene_Menu : public Scene
{
	size_t						m_selected{ 0 };
	std::vector<EntityPtr>		m_menuItems{};
	std::vector<std::string>	m_levelPaths{};

public:
	Scene_Menu() {}

	Scene_Menu(GameEngine* game)
		: Scene{ game }
	{
		init();
	}

	void loadMenu();

	void sAnimate();
	void draw(EntityPtr entity);
	void sRender();

	virtual void sDoAction(const Action& action);
	virtual void registerActions();
	virtual void update();
	void init();
};