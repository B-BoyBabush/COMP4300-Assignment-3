#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2		pos{};
	Vec2		prevPos{};
	Vec2		vel{};
	Vec2		scale{};
	sf::Angle	angle{};

	CTransform()
	{}

	CTransform(const Vec2& p = { 0.0f, 0.0f }, const Vec2& v = { 0.0f, 0.0f }, const Vec2& s = { 1.0f, 1.0f }, const sf::Angle& a)//add default value for angle
		: pos		{ p }
		, prevPos	{ p }
		, vel		{ v }
		, scale		{ s }
		, angle		{ a }
	{}
};

class CBoundingBox
{
public:
	const Vec2 size{};
	const Vec2 halfSize{};

	CBoundingBox()
	{}

	CBoundingBox(const Vec2& s)
		: size		{ s }
		, halfSize	{ s.x / 2, s.y / 2 }
	{}
};

class CInput
{
public:

};

class CAnimation
{
public:
	sf::Sprite sprite;

	CAnimation(sf::Texture& texture)
		: sprite{ texture }
	{
	}

};