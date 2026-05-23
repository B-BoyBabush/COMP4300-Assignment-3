#pragma once
#include "Entity.h"

#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

typedef std::shared_ptr<Entity> EntityPtr;
typedef std::vector<EntityPtr>	EntityVec;

class EntityManager
{
	EntityVec							m_entities{};
	EntityVec							m_toAdd{};
	std::map<std::string, EntityVec>	m_map{};

public:
	EntityPtr addEntity(std::string tag)
	{
		static size_t id{ 1 }; //Unique ID
		EntityPtr ptr{ std::make_shared<Entity>(Entity(tag, id)) };
		m_toAdd.push_back(ptr); //Add to queue
		m_map[tag].push_back(ptr);
		id++;

		return ptr;
	}

	void update()
	{
		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
			[](EntityPtr ptr) { return ptr->getStatus() == false;	}), m_entities.end()); //Erase entities that are dead

		for (auto& [tag, entityVec] : m_map) //Cycle through all vectors in map
		{
			entityVec.erase(std::remove_if(entityVec.begin(), entityVec.end(),
				[](EntityPtr ptr) { return ptr->getStatus() == false; }), entityVec.end()); //Erase map entities that are dead
		}

		for (EntityPtr e : m_toAdd)
		{
			m_entities.push_back(std::move(e));
		} //Add entities from queue to entities vector 

		m_toAdd.clear(); //Clear queue
	}

	const EntityVec& getEntities()
	{
		return m_entities;
	}

	const EntityVec& getEntities(const std::string& tag)
	{
		return m_map[tag];
	}
};