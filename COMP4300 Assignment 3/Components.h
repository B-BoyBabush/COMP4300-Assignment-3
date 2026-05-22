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
	Vec2 size{};
	Vec2 halfSize{};

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
	std::string m_state{ "idle" };
	bool m_facingRight{ true };

	CState() {}

	CState(const std::string& s)
		: m_state{ s }
		, m_facingRight{ true }
	{}
};

class CGravity : public Component
{
public:
	float gravity{ 0.0 };

	CGravity() {}

	CGravity(float g)
		: gravity{ g }
	{}
};