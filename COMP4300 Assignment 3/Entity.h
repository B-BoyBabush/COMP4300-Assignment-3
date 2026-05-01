#pragma once
#include <iostream>
#include "Components.h"
#include "EntityManager.h"

class Entity
{
	friend class EntityManager;

	std::string		tag{};
	int				id{};
	bool			isAlive{};

public:
	std::shared_ptr<CTransform>		cTransform{};
	std::shared_ptr<CBoundingBox>	cBoundingBox{};
	std::shared_ptr<CInput>			cInput{};
	std::shared_ptr<CAnimation>		cAnimation{};

	const std::string_view getTag() const
	{	return tag;	}

	const int& getID() const
	{	return id;	}

	const bool& getStatus() const
	{	return isAlive;	}

private:
	Entity()
	{}

	Entity(const std::string& t="none", const int& i=0, const bool& b=true)
		: tag{ t }
		, id{ i }
		, isAlive{ b }
	{}
};