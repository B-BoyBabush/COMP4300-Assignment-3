#pragma once
#include "Components.h"
#include "EntityManager.h"
#include <iostream>
#include <tuple>

class Entity
{
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

	Entity(const std::string& t = "none", const size_t& i = 0)
		: m_tag{ t }
		, m_id{ i }
		, m_isAlive{ true }
	{}
public:

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