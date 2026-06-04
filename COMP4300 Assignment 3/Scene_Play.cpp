#include "Scene_Play.h"
#include "Scene_Menu.h"
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

void Scene_Play::loadLevel(const std::string& levelPath)
{
	m_entities = EntityManager();
	
	std::ifstream fin{ levelPath };
	std::string type{};
	
	while (fin >> type)
	{
		if (type == "Player")
		{
			fin >> m_playerConfig.GX >> m_playerConfig.GY
				>> m_playerConfig.MX >> m_playerConfig.MY;

			spawnPlayer();
		}
		
		if (type == "Ground" || type == "Block" || type == "Brick" || type == "Question")
		{
			int gridX{};
			int gridY{};

			fin >> gridX >> gridY;
			
			EntityPtr tile = m_entities.addEntity("Tile");
			tile->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation(type), true);
			tile->addComponent<CTransform>(gridToMidPixel(gridX, gridY, tile));
			tile->addComponent<CBoundingBox>(tile->getComponent<CAnimation>().m_animation.m_intRect.size);
		}

		else if (type == "Background")
		{
			std::string backgroundName{}; //animation name of background
			int gridX{};
			int gridY{};

			fin >> backgroundName >> gridX >> gridY;

			EntityPtr background = m_entities.addEntity("Background");
			background->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation(backgroundName), true);
			background->addComponent<CTransform>(gridToMidPixel(gridX, gridY, background));
		}
	}

	fin.close();

	return;
}

void Scene_Play::spawnFireball()
{
	m_player->getComponent<CState>().m_state = "throwing";
	
	EntityPtr fireball = m_entities.addEntity("Fireball");
	fireball->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Fireball"), false);
	float velX{ (m_player->getComponent<CState>().m_facingRight ? 10.0f : -10.0f) };
	fireball->addComponent<CTransform>(m_player->getComponent<CTransform>().pos, Vec2{ velX, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
	fireball->addComponent<CBoundingBox>(fireball->getComponent<CAnimation>().m_animation.m_intRect.size);
	fireball->addComponent<CGravity>();
}

void Scene_Play::spawnPlayer()
{
	m_player = m_entities.addEntity("Player");
	m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioIdle"), true);
	m_player->addComponent<CTransform>(Vec2{ gridToMidPixel(m_playerConfig.GX, m_playerConfig.GY, m_player) });
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
		m_player->getComponent<CTransform>().vel.y = 0.0f;
	if (m_player->getComponent<CInput>().left == true)
		m_player->getComponent<CTransform>().vel.x += -5.0f;
	if (m_player->getComponent<CInput>().right == true)
		m_player->getComponent<CTransform>().vel.x += 5.0f;
	
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CGravity>())
			entity->getComponent<CTransform>().vel.y += entity->getComponent<CGravity>().gravity;
		
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
	for (EntityPtr entity : m_entities.getEntities("Tile"))
	{
		Vec2 overlap = physics.getOverlap(m_player, entity);
		
		//If there was an overlap with a tile
		if (overlap > Vec2{ 0.0f, 0.0f })
		{
			//Get the previous overlap too
			Vec2 prevOverlap = physics.getPrevOverlap(m_player, entity);
			
			//If coming from left or right
			if (prevOverlap.y > 0.0f)
			{
				//Move player left or right depending on previous position
				if (m_player->getComponent<CTransform>().prevPos.x > entity->getComponent<CTransform>().prevPos.x)
					m_player->getComponent<CTransform>().pos.x += overlap.x;
				else if (m_player->getComponent<CTransform>().prevPos.x < entity->getComponent<CTransform>().prevPos.x)
					m_player->getComponent<CTransform>().pos.x -= overlap.x;
			}

			//If coming from above or below
			if (prevOverlap.x > 0.0f)
			{
				//If player is below the tile
				if (m_player->getComponent<CTransform>().prevPos.y > entity->getComponent<CTransform>().prevPos.y)
				{
					//Push the player out and reset his velocity
					m_player->getComponent<CTransform>().pos.y += overlap.y;
					m_player->getComponent<CTransform>().vel.y = 0.0f;

					//Change to explosion and remove bounding box (and therefore collisions)
					if (entity->getComponent<CAnimation>().m_animation.m_name == "Brick")
					{
						entity->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Explosion"), false);
						entity->addComponent<CBoundingBox>();
						entity->getComponent<CBoundingBox>().has = false;
					}
					else if (entity->getComponent<CAnimation>().m_animation.m_name == "Question")
					{
						entity->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Question2"), true);
						
						EntityPtr coin = m_entities.addEntity("Coin");
						coin->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Coin"), false);
						coin->addComponent<CTransform>(Vec2{ entity->getComponent<CTransform>().pos.x, entity->getComponent<CTransform>().pos.y - 64 });
					}
				}
				//If player is above the tile
				if (m_player->getComponent<CTransform>().prevPos.y < entity->getComponent<CTransform>().prevPos.y)
				{
					//Push the player out and reset his velocity
					m_player->getComponent<CTransform>().pos.y -= overlap.y;
					m_player->getComponent<CTransform>().vel.y = 0.0f;

					//Set player to correct animation
					if (m_player->getComponent<CTransform>().vel.x != 0.0f)
						m_player->getComponent<CState>().m_state = "walking";
					if (m_player->getComponent<CTransform>().vel.x == 0.0f)
						m_player->getComponent<CState>().m_state = "idle";
				}
			}

			//To prevent shuttering when on the corner of a block
			if (prevOverlap < Vec2{ 0.0f, 0.0f })
			{
				if (m_player->getComponent<CTransform>().prevPos.x > entity->getComponent<CTransform>().prevPos.x)
					m_player->getComponent<CTransform>().pos.x += overlap.x;
				else if (m_player->getComponent<CTransform>().prevPos.x < entity->getComponent<CTransform>().prevPos.x)
					m_player->getComponent<CTransform>().pos.x -= overlap.x;
			}

			//To prevent being stopped when walking left on the ground as normal
			if (prevOverlap == Vec2{ 0.0f, 0.0f })
			{
				if (m_player->getComponent<CTransform>().prevPos.y > entity->getComponent<CTransform>().prevPos.y)
					m_player->getComponent<CTransform>().pos.y += overlap.y;
				else if (m_player->getComponent<CTransform>().prevPos.y < entity->getComponent<CTransform>().prevPos.y)
					m_player->getComponent<CTransform>().pos.y -= overlap.y;
			}
		}
	}

	for (EntityPtr fireball : m_entities.getEntities("Fireball"))
	{
		for (EntityPtr tile : m_entities.getEntities("Tile"))
		{
			Vec2 overlap = physics.getOverlap(fireball, tile);
			
			//If a fireball hits a tile
			if (overlap > Vec2{ 0.0f, 0.0f })
			{
				if (tile->getComponent<CAnimation>().m_animation.m_name == "Brick")
				{
					//Delete the fireball
					fireball->destroy();

					//Change the tile to an explosion and remove bounding box (and therefore collisions)
					tile->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("Explosion"), false);
					tile->addComponent<CBoundingBox>();
					tile->getComponent<CBoundingBox>().has = false;
				}
				else if (tile->getComponent<CAnimation>().m_animation.m_name == "Ground")
				{
					fireball->getComponent<CTransform>().pos.y -= overlap.y;
					fireball->getComponent<CTransform>().vel.y -= 14.f;
				}
				else
					fireball->destroy();
			}
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
			m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioWalk"), true);
		}
		else if (m_player->getComponent<CState>().m_state == "idle")
		{
			m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioIdle"), true);
		}
		else if (m_player->getComponent<CState>().m_state == "air")
		{
			m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioJump"), true);
		}
		else if (m_player->getComponent<CState>().m_state == "throwing")
		{
			m_player->addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation("MarioThrow"), true);
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

				auto hasEnded = [](Animation& a) ->bool { return (a.m_gameFrame / a.m_speed) >= a.m_totalFrames; };
				if (not entity->getComponent<CAnimation>().m_repeat && hasEnded(anim))
					entity->destroy();
			}
		}
	}
}

void Scene_Play::draw(EntityPtr entity)
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

void Scene_Play::sRender()
{
	m_gamePtr->setWindow().clear(sf::Color{100, 100, 255});

	//Entities drawn in specific order so entities like the player are in front
	for (EntityPtr entity : m_entities.getEntities("Background"))
		draw(entity);
	for (EntityPtr entity : m_entities.getEntities("Tile"))
		draw(entity);
	for (EntityPtr entity : m_entities.getEntities("Player"))
		draw(entity);
	for (EntityPtr entity : m_entities.getEntities("Explosion"))
		draw(entity);
	for (EntityPtr entity : m_entities.getEntities("Fireball"))
		draw(entity);
	for (EntityPtr entity : m_entities.getEntities("Coin"))
		draw(entity);

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
		else if (action.m_name == "ATTACK")
			m_player->getComponent<CInput>().attack = true;
		else if (action.m_name == "ESCAPE")
			m_gamePtr->changeScene("menu", std::make_shared<Scene_Menu>(m_gamePtr));
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
		else if (action.m_name == "ATTACK")
			spawnFireball();
	}
}

void Scene_Play::registerActions()
{
	m_actions[sf::Keyboard::Scancode::W] = "JUMP";
	m_actions[sf::Keyboard::Scancode::A] = "LEFT";
	m_actions[sf::Keyboard::Scancode::S] = "DOWN";
	m_actions[sf::Keyboard::Scancode::D] = "RIGHT";
	m_actions[sf::Keyboard::Scancode::Space] = "ATTACK";
	m_actions[sf::Keyboard::Scancode::Escape] = "ESCAPE";
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

void Scene_Play::init(const std::string& levelPath)
{	
	registerActions();
	loadLevel(levelPath);
}