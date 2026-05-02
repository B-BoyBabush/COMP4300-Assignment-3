#pragma once
#include <map>
#include "Entity.h"

class EntityManager
{
public:
	typedef std::shared_ptr<Entity> EntityPtr;
	typedef std::vector<EntityPtr> EntityVec;

private:
	EntityVec							m_entities{};
	EntityVec							m_toAdd{};
	std::map<std::string, EntityVec>	m_map{};

public:
	EntityPtr addEntity(std::string tag)
	{
		static size_t id{ 1 }; //Unique ID
		EntityPtr e{ std::make_shared<Entity>(Entity(tag, id)) };
		m_toAdd.emplace_back(e); //Add to queue
		m_map[tag].push_back(e);
		id++;

		return e;
	}

	void update()
	{
		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), 
			[](EntityPtr x) { return x->getStatus() == false;	}), m_entities.end()); //Erase entities that are dead

		for (auto& [tag, entityVec] : m_map) //Cycle through all vectors in map
		{
			entityVec.erase(std::remove_if(entityVec.begin(), entityVec.end(), 
				[](EntityPtr x) { return x->getStatus() == false; }), entityVec.end()); //Erase map entities that are dead
		}
		
		for (EntityPtr e : m_toAdd)
		{	
			m_entities.push_back(std::move(e));
		} //Add entities from queue to entities vector 

		m_toAdd.clear(); //Clear queue
	}

	const EntityVec& getEntities() const
	{
		return m_entities;
	}

	const EntityVec& getEntities(std::string& tag)
	{
		return m_map[tag];
	}
};