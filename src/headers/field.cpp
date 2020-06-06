#include "field.h"

void Field::ExecuteAllCmds(){
	bool Infected = false;
	int InfectedNum = -1;
	if (InfectionCounter >= InfectionTime){
		InfectedNum = rand() % 300;
	}
	int BotCounter = 0;
	for(int x = 0; x != width; x++){
		for (int y = 0; y != height; y++){
			if (bots[x][y].Exists && bots[x][y].Alive){
				bots[x][y].DoCommand(x, y, bots, width, height);
				if (bots[x][y].Infected){
					int DeathChance = rand() % 100;
					if (DeathChance < 3){
						bots[x][y].Alive = false;
					}
				}
				
				if (InfectedNum != -1 && BotCounter >= InfectedNum && !Infected){
					bots[x][y].Infected = true;
					int CmdNum = rand() % 64;
					bots[x][y].ChangeGen(CmdNum, 100);
					CmdNum = rand() % 64;
					bots[x][y].ChangeGen(CmdNum, 100);
					Infected = true;
				}
			}
			BotCounter++;
		}
	}
	InfectionCounter++;
	sf::sleep(sf::milliseconds(sleepMs));
}

void Field::AddBot(int x, int y, Bot SomeBot){
	bots[x][y] = SomeBot;
}

Field::Field(int sleepMs){
	this->sleepMs = sleepMs;
	bots = new Bot* [width];
	for (int x = 0; x != width; x++){
		bots[x] = new Bot[height];
	}
	int EmptyCmd[64];
	for (int i = 0; i != 64; i++){
		EmptyCmd[i] = 2;
	}
	Bot EmptyBot;
	EmptyBot.Setup(EmptyCmd, false, 200, 0);
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
				if (bots[x][y].Infected){
					AliveBot.setFillColor(sf::Color(201, 0, 122));
				}
				window.draw(AliveBot);
			}
		}
	}
}
