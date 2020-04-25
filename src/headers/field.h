#pragma once

#include "bot.h"
#include <SFML/Graphics.hpp>

class Field{
public:
	Field(bool debug);
	void ExecuteAllCmds();
	void AddBot(int x, int y, Bot SomeBot);
	void Draw(sf::RenderWindow &window);
private:
	int height = 60;
	int weidth = 100;
	Bot bots[60][100];
	bool Debug = false;
	int InfectionTime = 100;
	int InfectionCounter = 0;
};