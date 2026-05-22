#include "Physics.h"
#include "Components.h"

Vec2 Physics::getOverlap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
	if (first->hasComponent<CBoundingBox>() && second->hasComponent<CBoundingBox>())
	{
		float xDistance{ std::abs(first->getComponent<CTransform>().pos.x - second->getComponent<CTransform>().pos.x) };
		float xSize{ first->getComponent<CBoundingBox>().halfSize.x + second->getComponent<CBoundingBox>().halfSize.x };
		float xOverlap{ xSize - xDistance };

		float yDistance{ std::abs(first->getComponent<CTransform>().pos.y - second->getComponent<CTransform>().pos.y) };
		float ySize{ first->getComponent<CBoundingBox>().halfSize.y + second->getComponent<CBoundingBox>().halfSize.y };
		float yOverlap{ ySize - yDistance };

		return Vec2{ xOverlap, yOverlap };
	}
	else
		return Vec2{ 0.0f, 0.0f };
}

Vec2 Physics::getPrevOverlap(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second)
{
	if (first->hasComponent<CBoundingBox>() && second->hasComponent<CBoundingBox>())
	{
		float xDistance{ std::abs(first->getComponent<CTransform>().prevPos.x - second->getComponent<CTransform>().prevPos.x) };
		float xSize{ first->getComponent<CBoundingBox>().halfSize.x + second->getComponent<CBoundingBox>().halfSize.x };
		float xOverlap{ xSize - xDistance };

		float yDistance{ std::abs(first->getComponent<CTransform>().prevPos.y - second->getComponent<CTransform>().prevPos.y) };
		float ySize{ first->getComponent<CBoundingBox>().halfSize.y + second->getComponent<CBoundingBox>().halfSize.y };
		float yOverlap{ ySize - yDistance };

		return Vec2{ xOverlap, yOverlap };
	}
	else
		return Vec2{ 0.0f, 0.0f };
}