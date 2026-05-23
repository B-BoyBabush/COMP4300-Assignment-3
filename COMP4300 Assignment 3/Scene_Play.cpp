#include "Scene_Play.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GameEngine.h"
#include "Action.h"
#include "Physics.h"

#include <fstream>

Vec2 Scene_Play::gridToMidPixel(int gridX, int gridY, EntityPtr entity)
{
	Vec2 coord{ gridX, gridY };
	coord *= 64;
	coord += entity->getComponent<CAnimation>().m_animation.m_intRect.size / 2;
	coord.y = m_gamePtr->getWindow().getSize().y - coord.y;
	
	return coord;
}

void Scene_Play::loadLevel()
{
	m_entities = EntityManager();
	spawnPlayer();
	
	std::ifstream fin{ "C:/Libraries/Assets/Level_One.txt" };
	std::string tileType{};
	
	while (fin >> tileType)
	{
		if (tileType == "Ground")
		{
			int gridX{};
			int gridY{};

			fin >> gridX >> gridY;
			
			EntityPtr ground = m_entities.addEntity("Ground");
			ground->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Ground"));
			ground->addComponent<CTransform>(gridToMidPixel(gridX, gridY, ground), Vec2{ 0.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
			ground->addComponent<CBoundingBox>(ground->getComponent<CAnimation>().m_animation.m_intRect.size);
		}

		else if (tileType == "Block")
		{
			int gridX{};
			int gridY{};

			fin >> gridX >> gridY;

			EntityPtr block = m_entities.addEntity("Block");
			block->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Block"));
			block->addComponent<CTransform>(gridToMidPixel(gridX, gridY, block), Vec2{ 0.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
			block->addComponent<CBoundingBox>(block->getComponent<CAnimation>().m_animation.m_intRect.size);
		}

		else if (tileType == "Brick")
		{
			int gridX{};
			int gridY{};

			fin >> gridX >> gridY;

			EntityPtr brick = m_entities.addEntity("Brick");
			brick->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Brick"));
			brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick), Vec2{ 0.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
			brick->addComponent<CBoundingBox>(brick->getComponent<CAnimation>().m_animation.m_intRect.size);
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
	m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioIdle"));
	m_player->addComponent<CTransform>(Vec2{ gridToMidPixel(2, 1, m_player) }, Vec2{0.0f, 0.0f}, Vec2{1.0f, 1.0f}, 0.0f);
	m_player->addComponent<CBoundingBox>(m_player->getComponent<CAnimation>().m_animation.m_intRect.size);
	m_player->addComponent<CInput>();
	m_player->addComponent<CState>();
	m_player->addComponent<CGravity>();
}

void Scene_Play::sMovement()
{
	m_player->getComponent<CTransform>().vel = { 0.0f, m_player->getComponent<CTransform>().vel.y };

	//Add player input
	if (m_player->getComponent<CInput>().up == true)
	{
		if (m_player->getComponent<CState>().m_state != "air")
		{
			m_player->getComponent<CTransform>().vel.y = -16.0f;
			m_player->getComponent<CState>().m_state = "air";
		}
	}
	if (m_player->getComponent<CInput>().up == false && m_player->getComponent<CTransform>().vel.y < 0.0f)
		m_player->getComponent<CTransform>().vel.y -= m_player->getComponent<CTransform>().vel.y;
	if (m_player->getComponent<CInput>().left == true)
		m_player->getComponent<CTransform>().vel.x += -5.0f;
	if (m_player->getComponent<CInput>().right == true)
		m_player->getComponent<CTransform>().vel.x += 5.0f;

	m_player->getComponent<CTransform>().vel.y += m_player->getComponent<CGravity>().gravity;
	
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CTransform>())
		{			
			entity->getComponent<CTransform>().prevPos = entity->getComponent<CTransform>().pos;
			entity->getComponent<CTransform>().pos += entity->getComponent<CTransform>().vel;
		}
	}
}

void Scene_Play::sCollision()
{
	Physics physics{};
	for (EntityPtr entity : m_entities.getEntities("Ground"))
	{
		Vec2 overlap = physics.getOverlap(m_player, entity);
		if (overlap > Vec2{ 0.0f, 0.0f })
		{
			m_player->getComponent<CTransform>().vel.y = 0.0f;
			m_player->getComponent<CTransform>().prevPos.y = m_player->getComponent<CTransform>().pos.y;
			m_player->getComponent<CTransform>().pos.y -= overlap.y;
				
			if (m_player->getComponent<CTransform>().vel.x != 0.0f)
				m_player->getComponent<CState>().m_state = "walking";
			if (m_player->getComponent<CTransform>().vel.y != 0.0f)
				m_player->getComponent<CState>().m_state = "air";
			if (m_player->getComponent<CTransform>().vel.x == 0.0f)
				m_player->getComponent<CState>().m_state = "idle";
		}
	}

	for (EntityPtr entity : m_entities.getEntities("Block"))
	{
		Vec2 overlap = physics.getOverlap(m_player, entity);
		if (overlap > Vec2{ 0.0f, 0.0f })
		{
			m_player->getComponent<CTransform>().vel.y = 0.0f;
			m_player->getComponent<CTransform>().prevPos.y = m_player->getComponent<CTransform>().pos.y;
			m_player->getComponent<CTransform>().pos.y -= overlap.y;

			if (m_player->getComponent<CTransform>().vel.x != 0.0f)
				m_player->getComponent<CState>().m_state = "walking";
			if (m_player->getComponent<CTransform>().vel.y != 0.0f)
				m_player->getComponent<CState>().m_state = "air";
			if (m_player->getComponent<CTransform>().vel.x == 0.0f)
				m_player->getComponent<CState>().m_state = "idle";
		}
	}
}

void Scene_Play::sState()
{	
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CState>())
		{
			if (entity->getComponent<CTransform>().vel.x > 0.0f)
				entity->getComponent<CState>().m_facingRight = true;
			if (entity->getComponent<CTransform>().vel.x < 0.0f)
				entity->getComponent<CState>().m_facingRight = false;
		}
	}
}

void Scene_Play::sAnimate()
{	
	//Change player's animation to be consistent with their state (if necessary)
	static std::string lastState{};
	if (m_player->getComponent<CState>().m_state != lastState)
	{
		lastState = m_player->getComponent<CState>().m_state;

		if (m_player->getComponent<CState>().m_state == "walking")
		{
			m_player->getComponent<CAnimation>().m_animation = m_gamePtr->getAssets().getAnimation("MarioWalk");
		}
		else if (m_player->getComponent<CState>().m_state == "idle")
		{
			m_player->getComponent<CAnimation>().m_animation = m_gamePtr->getAssets().getAnimation("MarioIdle");
		}
		else if (m_player->getComponent<CState>().m_state == "air")
		{
			m_player->getComponent<CAnimation>().m_animation = m_gamePtr->getAssets().getAnimation("MarioJump");
		}
	}
	
	//Update all animations
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
			}
		}
	}
}

void Scene_Play::sRender()
{
	m_gamePtr->setWindow().clear(sf::Color{100, 100, 255});

	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{			
			sf::Sprite sprite{ *entity->getComponent<CAnimation>().m_animation.m_txtrPtr,
								entity->getComponent<CAnimation>().m_animation.m_intRect };
			
			sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
			sprite.setPosition(entity->getComponent<CTransform>().pos.toVec2f());

			if (entity->hasComponent<CState>())
			{
				if (entity->getComponent<CState>().m_facingRight == true)
					sprite.scale({ 1.0f, 1.0f });
				else if (entity->getComponent<CState>().m_facingRight == false)
					sprite.scale({ -1.0f, 1.0f });
			}

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
	sCollision();
	sState();
	sAnimate();
	sRender();

	m_currentFrame++;
}

void Scene_Play::init()
{	
	registerActions();
	loadLevel();
}