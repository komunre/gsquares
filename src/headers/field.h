#pragma once

#include "bot.h"
#include <SFML/Graphics.hpp>

class Field{
public:
	Field(int sleepMs);
	void ExecuteAllCmds();
	void AddBot(int x, int y, Bot SomeBot);
	void Draw(sf::RenderWindow &window);
	const int height = 70;
	const int width = 100;
private:
	Bot **bots;
	int InfectionCounter;
	int InfectionTime = 300;
	int sleepMs = 0;
};
