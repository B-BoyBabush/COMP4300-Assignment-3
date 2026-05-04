#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"

class Component
{
public:
	bool has{ false };
};

class CTransform : public Component
{
public:
	Vec2		pos{};
	Vec2		prevPos{};
	Vec2		vel{};
	Vec2		scale{};
	float		angle{};

	CTransform(const Vec2& p = { 0.0f, 0.0f }, const Vec2& v = { 0.0f, 0.0f }, const Vec2& s = { 1.0f, 1.0f }, const float& a=0.0f)//add default value for angle
		: pos		{ p }
		, prevPos	{ p }
		, vel		{ v }
		, scale		{ s }
		, angle		{ a }
	{
		has = true;
	}
};

class CBoundingBox : public Component
{
public:
	const Vec2 size{};
	const Vec2 halfSize{};

	CBoundingBox(const Vec2& s={10.0f, 10.0f})
		: size		{ s }
		, halfSize	{ s.x / 2, s.y / 2 }
	{	has = true;	}
};

class CInput : public Component
{
public:
	bool up{ false };
	bool down{ false };
	bool left{ false };
	bool right{ false };

	CInput()
	{	has = true;	}
};

class CAnimation : public Component
{
public:
	CAnimation()
	{
		has = true;
	}

	CAnimation(sf::Texture& texture)
	{
		has = true;
	}

};