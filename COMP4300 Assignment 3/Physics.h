#pragma once
#include "Vec2.h"
#include "Entity.h"
#include <memory>

class Physics
{
public:
	Vec2 getOverlap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);
	Vec2 getPrevOverlap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second);

	Physics() {}
};