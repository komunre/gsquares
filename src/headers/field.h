#pragma once

#include "bot.h"
#include <SFML/Graphics.hpp>

class Field{
public:
	Field(int sleepMs);
	void ExecuteAllCmds();
	void AddBot(int x, int y, Bot SomeBot);
	void Draw(sf::RenderWindow &window);
	const int height = 70; //Field height
	const int width = 100; //Field width
private:
	Bot **bots; //Field of the bots
	int InfectionCounter;
	int InfectionTime = 300; //Every n turns infect one bot
	int sleepMs = 0; //Slow down process
};
