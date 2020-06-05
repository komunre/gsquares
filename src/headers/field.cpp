#include "field.h"

void Field::ExecuteAllCmds(){
	for(int x = 0; x != height; x++){
		for (int y = 0; y != width; y++){
			if (bots[x][y].Exists && bots[x][y].Alive){
				bots[x][y].DoCommand(x, y, bots, width, height);
			}
		}
	}
}

void Field::AddBot(int x, int y, Bot SomeBot){
	bots[x][y] = SomeBot;
}

Field::Field(){
	bots = new Bot* [width];
	for (int x = 0; x != width; x++){
		bots[x] = new Bot[height];
	}
	int EmptyCmd[64];
	for (int i = 0; i != 64; i++){
		EmptyCmd[i] = 2;
	}
	Bot EmptyBot;
	EmptyBot.Setup(EmptyCmd, false, 200);
	for (int x = 0; x != height; x++){
		for (int y = 0; y != width; y++){
			bots[x][y] = EmptyBot;
		}
	}
}

void Field::Draw(sf::RenderWindow &window){
	for(int x = 0; x != width; x++){
		for (int y = 0; y != height; y++){
			if (!bots[x][y].Exists){
				
			}
			else if (!bots[x][y].Alive){
				sf::RectangleShape DeadBot(sf::Vector2f(10, 10));
				DeadBot.setPosition(x * 10, y * 10);
				DeadBot.setFillColor(sf::Color(195, 195, 195));
				window.draw(DeadBot);
			}
			else{
				sf::RectangleShape AliveBot(sf::Vector2f(10, 10));
				AliveBot.setPosition(x * 10, y * 10);
				if (bots[x][y].PhsCount > bots[x][y].EatCount){
					AliveBot.setFillColor(sf::Color(100, 250, 50));
				}
				else{
					AliveBot.setFillColor(sf::Color(255, 0, 0));
				}
				window.draw(AliveBot);
			}
		}
	}
}
