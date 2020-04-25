#include "field.h"

void Field::ExecuteAllCmds(){
	bool Infected = false;
	int InfectedNum = -1;
	if (InfectionCounter >= InfectionTime){
		InfectedNum = rand() % 300;
	}
	int BotCounter = 0;
	for(int y = 0; y != height; y++){
		for (int x = 0; x != weidth; x++){
			if (bots[y][x].Exists && bots[y][x].Alive){
				if (Debug){
					std::cout << "[" << y << "][" << x << "] Executing bot..." << std::endl;
					std::cout << bots[y][x].GetRepl() << std::endl;
				}
				bots[y][x].DoCommand(x, y, bots);
				if (bots[y][x].Infected){
					int DeathChance = rand() % 100;
					if (DeathChance < 3){
						bots[y][x].Alive = false;
					}
				}
				
				if (InfectedNum != -1 && BotCounter >= InfectedNum && !Infected){
					bots[y][x].Infected = true;
					int CmdNum = rand() % 64;
					bots[y][x].ChangeGen(CmdNum, 100);
					CmdNum = rand() % 64;
					bots[y][x].ChangeGen(CmdNum, 100);
					Infected = true;
				}
			}
			BotCounter++;
		}
	}
	InfectionCounter++;
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
				if (bots[y][x].Infected){
					AliveBot.setFillColor(sf::Color(201, 0, 122));
				}
				window.draw(AliveBot);
			}
		}
	}
}