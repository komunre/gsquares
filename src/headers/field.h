#pragma once

#include "bot.h"
#include <SFML/Graphics.hpp>

class Field{
public:
	Field();
	void ExecuteAllCmds();
	void AddBot(int x, int y, Bot SomeBot);
	void Draw(sf::RenderWindow &window);
	const int height = 80;
	const int width = 100;
private:
	Bot **bots;
};
