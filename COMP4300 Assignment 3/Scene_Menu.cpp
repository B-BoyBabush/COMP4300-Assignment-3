#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "EntityManager.h"
#include "Animation.h"

#include "SFML/Graphics.hpp"

#include <vector>
#include <map>
#include <fstream>

void Scene_Menu::loadMenu()
{
	m_menuItems.clear();
	std::ifstream fin{ "Assets/MenuConfig.txt" };

	std::string name{};

	while (fin >> name)
	{
		int x{};
		int y{};
		bool selectable{};
		std::string levelPath{};

		fin >> selectable >> x >> y;

		EntityPtr entity = m_entities.addEntity(name);
		entity->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation(name), true);
		entity->addComponent<CTransform>(Vec2{ x, y });

		if (selectable)
		{
			m_menuItems.push_back(entity);

			fin >> levelPath;
			m_levelPaths.push_back(levelPath);
		}
	}
}

void Scene_Menu::sAnimate()
{
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			Animation& anim = entity->getComponent<CAnimation>().m_animation;
			if (anim.m_name != "")
			{
				anim.m_animFrame = (anim.m_gameFrame / anim.m_speed) % anim.m_totalFrames;
				anim.m_intRect.position.x = anim.m_animFrame * anim.m_intRect.size.x;
				anim.m_gameFrame++;

				auto hasEnded = [](Animation& a) -> bool { return (a.m_gameFrame / a.m_speed) >= a.m_totalFrames; };
				if (not entity->getComponent<CAnimation>().m_repeat && hasEnded(anim))
					entity->destroy();
			}
		}
	}
}

void Scene_Menu::draw(EntityPtr entity)
{
	if (entity->hasComponent<CAnimation>())
	{
		sf::Sprite sprite{ 
			*entity->getComponent<CAnimation>().m_animation.m_txtrPtr,
			entity->getComponent<CAnimation>().m_animation.m_intRect 
		};

		sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
		sprite.setPosition(entity->getComponent<CTransform>().pos.toVec2f());
		sprite.scale(sf::Vector2f{ 3.0f, 3.0f });

		if (entity != m_menuItems[m_selected])
			sprite.setColor(sf::Color::Black);

		m_gamePtr->setWindow().draw(sprite);
	}
}

void Scene_Menu::sRender()
{
	m_gamePtr->setWindow().clear(sf::Color{ 100, 100, 255 });

	for (EntityPtr entity : m_entities.getEntities())
		draw(entity);

	m_gamePtr->setWindow().display();
}

void Scene_Menu::sDoAction(const Action& action)
{
	if (action.m_type == "START")
	{
		if (action.m_name == "UP")
		{
			--m_selected;
			if (m_selected >= m_menuItems.size())
				m_selected = m_menuItems.size() - 1;
		}
		if (action.m_name == "DOWN")
		{
			++m_selected;
			if (m_selected >= m_menuItems.size())
				m_selected = 0;
		}
		if (action.m_name == "SELECT")
		{
			m_gamePtr->changeScene("play", std::make_shared<Scene_Play>(m_gamePtr, m_levelPaths[m_selected]));
		}
		if (action.m_name == "BACK")
		{
			m_gamePtr->setWindow().close();
		}
	}
}

void Scene_Menu::registerActions()
{
	m_actions[sf::Keyboard::Scancode::W] = "UP";
	m_actions[sf::Keyboard::Scancode::S] = "DOWN";
	m_actions[sf::Keyboard::Scancode::D] = "SELECT";
	m_actions[sf::Keyboard::Scancode::Escape] = "BACK";
}

void Scene_Menu::update()
{
	m_entities.update();

	sAnimate();
	sRender();

	m_currentFrame++;
}

void Scene_Menu::init()
{
	registerActions();
	loadMenu();
}