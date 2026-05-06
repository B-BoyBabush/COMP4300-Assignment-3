#include "Vec2.h"
#include "EntityManager.h"
#include "Entity.h"
#include "GameEngine.cpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
	GameEngine superMario{};
	superMario.init();
	superMario.run();

	return 0;
}