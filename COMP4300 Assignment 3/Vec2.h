#pragma once

#include <iostream>

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

	Vec2 operator+(Vec2 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2 operator-(Vec2 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2 operator*(Vec2 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vec2 operator/(Vec2 rhs)
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