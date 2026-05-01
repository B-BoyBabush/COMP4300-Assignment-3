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
	EntityPtr& addEntity(std::string tag)
	{
		static unsigned int id{ 1 }; //Unique ID
		EntityPtr e = std::make_shared<Entity>(tag, id, true);
		m_toAdd.push_back(e); //Add to queue
		id++;

		return e;
	}

	void update()
	{
		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](EntityPtr x) { return !x->getStatus();	})); //Erase entities that are dead
		m_map.erase(std::remove_if(m_map.begin(), m_map.end(), [](EntityPtr x) { return !x->getStatus(); })); //Erase map entities that are dead
		
		for (EntityPtr e : m_toAdd)
		{	
			m_entities.push_back(std::move(e));
			m_map.emplace(e->getTag(), e);
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