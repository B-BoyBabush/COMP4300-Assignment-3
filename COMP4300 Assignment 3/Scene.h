#pragma once
#include <map>
#include "EntityManager.h"
#include "Action.h"
#include "GameEngine.h"

class Scene
{
protected:
	typedef std::shared_ptr<Entity> EntityPtr;

	GameEngine*										m_gamePtr{ nullptr };
	std::map<sf::Keyboard::Scancode, std::string>	m_actions{};
	EntityManager									m_entities{};
	size_t											m_currentFrame{ 0 };

	Scene() {}

	Scene(GameEngine* game)
		: m_gamePtr{ game }
	{}

public:
	virtual ~Scene() = default;

	virtual void sDoAction(const Action& action) = 0;
	virtual void registerActions() = 0;
	virtual void update() = 0;
	virtual void init() = 0;

	std::string& getActions(const sf::Keyboard::Scancode& key) { return m_actions[key]; }
};