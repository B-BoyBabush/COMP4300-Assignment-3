#pragma once

#include <SFML/System.hpp>

#include <iostream>
#include <cmath>

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

	Vec2(const int& inx, const int& iny)
		: x{ static_cast<float>(inx) }
		, y{ static_cast<float>(iny) }
	{
	}

	Vec2(sf::Vector2f vec2f)
		: x{ vec2f.x }
		, y{ vec2f.y }
	{}

	Vec2(sf::Vector2i vec2i)
		: x{ static_cast<float>(vec2i.x) }
		, y{ static_cast<float>(vec2i.y) }
	{
	}

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

	Vec2 operator+=(int num)
	{
		x = x + num;
		y = y + num;
		return *this;
	}

	Vec2 operator-=(int num)
	{
		x -= num;
		y -= num;
		return *this;
	}

	Vec2 operator*=(int num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	Vec2 operator/=(int num)
	{
		x /= num;
		y /= num;
		return *this;
	}

	bool operator==(Vec2 rhs)
	{
		if (x == rhs.x && y == rhs.y)
			return true;
		else
			return false;
	}

	bool operator>(Vec2 rhs)
	{
		if (x > rhs.x && y > rhs.y)
			return true;
		else
			return false;
	}

	bool operator<(Vec2 rhs)
	{
		if (x < rhs.x && y < rhs.y)
			return true;
		else
			return false;
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