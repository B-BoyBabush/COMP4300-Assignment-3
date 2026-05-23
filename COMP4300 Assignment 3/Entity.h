#pragma once
#include "Components.h"

#include <tuple>
#include <iostream>

class EntityManager;

class Entity
{
public:
	friend class EntityManager;

	typedef std::tuple
		<CTransform,
		CBoundingBox,
		CInput,
		CAnimation, 
		CState,
		CGravity>
		ComponentTuple;

	std::string		m_tag{};
	size_t			m_id{};
	bool			m_isAlive{ true };
	ComponentTuple	m_components;

	Entity()
	{
	}

	Entity(const std::string& t = "none", const size_t& i = 0)
		: m_tag{ t }
		, m_id{ i }
		, m_isAlive{ true }
	{}

	const std::string& getTag() const
	{
		return m_tag;
	}

	const size_t& getID() const
	{
		return m_id;
	}

	const bool& getStatus() const
	{
		return m_isAlive;
	}

	void destroy()
	{
		m_isAlive = false;
	}

	template <typename T>
	T& getComponent()
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	bool hasComponent()
	{
		return getComponent<T>().has;
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T& component = getComponent<T>();
		component = T{ std::forward<TArgs>(mArgs)... };
		component.has = true;
		return component;
	}
};