#include "field.h"

void Field::ExecuteAllCmds(){
	for(int y = 0; y != height; y++){
		for (int x = 0; x != weidth; x++){
			if (bots[y][x].Exists && bots[y][x].Alive){
				if (Debug){
					std::cout << "[" << y << "][" << x << "] Executing bot..." << std::endl;
					std::cout << bots[y][x].GetRepl() << std::endl;
				}
				bots[y][x].DoCommand(x, y, bots);
			}
		}
	}
}

void Field::AddBot(int x, int y, Bot SomeBot){
	bots[x][y] = SomeBot;
}

Field::Field(bool debug){
	int EmptyCmd[64];
	for (int i = 0; i != 64; i++){
		EmptyCmd[i] = 2;
	}
	Bot EmptyBot;
	EmptyBot.Setup(EmptyCmd, false, 200);
	for (int y = 0; y != height; y++){
		for (int x = 0; x != weidth; x++){
			bots[y][x] = EmptyBot;
		}
	}
	Debug = debug;
}

void Field::Draw(sf::RenderWindow &window){
	for(int y = 0; y != height; y++){
		for (int x = 0; x != weidth; x++){
			if (!bots[y][x].Exists){
				
			}
			else if (!bots[y][x].Alive){
				sf::RectangleShape DeadBot(sf::Vector2f(10, 10));
				DeadBot.setPosition(x * 10, y * 10);
				DeadBot.setFillColor(sf::Color(195, 195, 195));
				window.draw(DeadBot);
			}
			else{
				sf::RectangleShape AliveBot(sf::Vector2f(10, 10));
				AliveBot.setPosition(x * 10, y * 10);
				if (bots[y][x].PhsCount > bots[y][x].EatCount){
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