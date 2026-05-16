#pragma once
#include <iostream>

class Action
{
public:
	std::string m_name{ "none" };
	std::string m_type{ "start" };

	Action() {}

	Action(const std::string& name, const std::string& type)
		: m_name{ name }
		, m_type{ type }
	{}
};