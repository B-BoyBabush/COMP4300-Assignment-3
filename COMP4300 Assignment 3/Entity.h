#pragma once
#include <iostream>
#include "Components.h"
#include "EntityManager.h"

class Entity
{
	friend class EntityManager;

public:
	std::string		m_tag{};
	size_t			m_id{};
	bool			m_isAlive{ true };

	std::tuple<CTransform,
		CBoundingBox,
		CInput,
		CAnimation>
		m_components{};

	Entity(const std::string& t = "none", const size_t& i = 0)
		: m_tag{ t }
		, m_id{ i }
	{
	}

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

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T& component = getComponent<T>();
		component = T{ std::forward<T>(mArgs...)};
		component.has = true;
		return component;
	}
};