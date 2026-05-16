#pragma once
#include "Vec2.h"
#include "Animation.h"

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

	CTransform()
	{}

	CTransform(const Vec2& p, const Vec2& v, const Vec2& s, const float& a)
		: pos		{ p }
		, prevPos	{ p }
		, vel		{ v }
		, scale		{ s }
		, angle		{ a }
	{}
};

class CBoundingBox : public Component
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

class CInput : public Component
{
public:
	bool up{};
	bool down{};
	bool left{};
	bool right{};

	CInput()
	{}
};

class CAnimation : public Component
{
public:
	Animation m_animation{};

	CAnimation(Animation& anim)
		: m_animation{ anim }
	{}

	CAnimation() {}
};

class CState : public Component
{
public:
	std::string state{ "idle" };
	//don't like this. Can it all be one variable? And make it so there's only one bool that can be true at once?

	CState() {}
};