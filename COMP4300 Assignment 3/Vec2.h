#pragma once

#include <iostream>
#include <SFML/System.hpp>

class Vec2
{
public:
	float x{};
	float y{};

	Vec2()
	{}

	Vec2(const float& inx, const float& iny)
		: x{ inx }
		, y{ iny }
	{}

	Vec2(sf::Vector2f vec2f)
		: x{ vec2f.x }
		, y{ vec2f.y }
	{}

	sf::Vector2f toVec2f()
	{
		return sf::Vector2f{ x, y };
	}

	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2{ x + rhs.x, y + rhs.y };
	}

	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2{ x - rhs.x, y - rhs.y };
	}

	Vec2 operator*(const float& val) const
	{
		return Vec2{ x * val, y * val };
	}

	Vec2 operator/(const float& val) const
	{
		return Vec2{ x / val, y / val };
	}

	Vec2 operator+=(Vec2 rhs)
	{
		x = x + rhs.x;
		y = y + rhs.y;
		return *this;
	}

	Vec2 operator-=(Vec2 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2 operator*=(Vec2 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vec2 operator/=(Vec2 rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vec2 normalize()
	{
		float c = std::sqrt(x * x + y * y);
		x /= c;
		y /= c;
		return *this;
	}

	const double length() const 
	{
		double c = std::sqrt(x * x + y * y);
		return c;
	}

	const void print() const
	{
		std::cout << x << " " << y << '\n';
	} //FOR TESTING PURPOSES ONLY
};