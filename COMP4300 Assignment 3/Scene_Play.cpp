#pragma once
#include "Scene_Play.h"
#include "Action.h"
#include <fstream>

Vec2 Scene_Play::gridToMidPixel(int gridX, int gridY)
{
	Vec2 coord{ gridX, gridY };
	coord *= 64;
	coord += 32;
	coord.y = m_gamePtr->getWindow().getSize().y - coord.y;
	
	return coord;
}

void Scene_Play::loadLevel()
{
	std::ifstream fin{ "C:/Libraries/Assets/Level_One.txt" };

	std::string tileType{};
	while (fin >> tileType)
	{
		if (tileType == "Block")
		{
			int gridX{};
			int gridY{};

			fin >> gridX >> gridY;
			
			EntityPtr block = m_entities.addEntity("Block");
			block->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Block"));
			block->addComponent<CTransform>(gridToMidPixel(gridX, gridY), Vec2{ 0.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
			block->addComponent<CBoundingBox>(block->getComponent<CAnimation>().m_animation.m_intRect.size);
		}
	}

	fin.close();

	return;
}

void Scene_Play::spawnEnemy()
{

}

void Scene_Play::spawnPlayer()
{
	m_player = m_entities.addEntity("player");
	m_player->addComponent<CTransform>(Vec2{ gridToMidPixel(1, 2) }, Vec2{0.0f, 0.0f}, Vec2{1.0f, 1.0f}, 0.0f);
	m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Bowser"));
	m_player->addComponent<CInput>();
	m_player->addComponent<CState>();
	m_player->addComponent<CGravity>();
}

void Scene_Play::sMovement()
{
	//PLAYER MOVEMENT
	if (m_player->getComponent<CInput>().up == true)
	{
		m_player->getComponent<CTransform>().vel.y = -3.0f;
	}
	if (m_player->getComponent<CInput>().left == true)
	{
		m_player->getComponent<CTransform>().pos.x += -3.0f;
		m_player->getComponent<CState>().state = "walkingLeft";
	}
	if (m_player->getComponent<CInput>().down == true)
	{
		m_player->getComponent<CTransform>().pos.y += 3.0f;
	}
	if (m_player->getComponent<CInput>().right == true)
	{
		m_player->getComponent<CTransform>().pos.x += 3.0f;
		m_player->getComponent<CState>().state = "walkingRight";
	}//PLAYER MOVEMENT
	
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CTransform>())
		{
			if (entity->hasComponent<CGravity>())
				entity->getComponent<CTransform>().vel.y += entity->getComponent<CGravity>().gravity;
			
			entity->getComponent<CTransform>().pos += entity->getComponent<CTransform>().vel;
		}
	}
}

void Scene_Play::sAnimate()
{
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			Animation& anim = entity->getComponent<CAnimation>().m_animation;
			anim.m_animFrame = (anim.m_gameFrame / anim.m_speed) % anim.m_totalFrames;
			anim.m_intRect.position.x = anim.m_animFrame * anim.m_intRect.size.x;
			anim.m_gameFrame++;
		}
	}
}

void Scene_Play::sRender()
{
	m_gamePtr->setWindow().clear(sf::Color{50, 20, 200});
	

	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{			
			sf::Sprite sprite{ *entity->getComponent<CAnimation>().m_animation.m_txtrPtr,
								entity->getComponent<CAnimation>().m_animation.m_intRect };
			
			sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
			sprite.setPosition(entity->getComponent<CTransform>().pos.toVec2f());

			//DELETE
			if (entity->hasComponent<CState>())
			{
				if (entity->getComponent<CState>().state == "walkingLeft")
					sprite.scale({ -1.0f, 1.0f });
			}
			//DELETE

			m_gamePtr->setWindow().draw(sprite);
		}
	}

	m_gamePtr->setWindow().display();
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.m_type == "START")
	{
		if (action.m_name == "JUMP")
			m_player->getComponent<CInput>().up = true;
		else if (action.m_name == "LEFT")
			m_player->getComponent<CInput>().left = true;
		else if (action.m_name == "DOWN")
			m_player->getComponent<CInput>().down = true;
		else if (action.m_name == "RIGHT")
			m_player->getComponent<CInput>().right = true;
	}
	if (action.m_type == "END")
	{
		if (action.m_name == "JUMP")
			m_player->getComponent<CInput>().up = false;
		else if (action.m_name == "LEFT")
			m_player->getComponent<CInput>().left = false;
		else if (action.m_name == "DOWN")
			m_player->getComponent<CInput>().down = false;
		else if (action.m_name == "RIGHT")
			m_player->getComponent<CInput>().right = false;
	}
}

void Scene_Play::registerActions()
{
	m_actions[sf::Keyboard::Scancode::Space] = "JUMP";
	m_actions[sf::Keyboard::Scancode::A] = "LEFT";
	m_actions[sf::Keyboard::Scancode::S] = "DOWN";
	m_actions[sf::Keyboard::Scancode::D] = "RIGHT";
}

void Scene_Play::update()
{
	m_entities.update();

	sMovement();
	sAnimate();
	sRender();

	m_currentFrame++;
}

void Scene_Play::init()
{	
	registerActions();
	loadLevel();
	spawnPlayer();
}