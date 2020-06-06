#include "bot.h"

Bot::Bot(){}

void Bot::Setup(int cmd[64], bool exst, int AmEnergy, int age){
	for (int x = 0; x != 64; x++){
		cmds[x] = cmd[x];
	}
	Exists = exst;
	Energy = AmEnergy;
	this->age = age;
}

void Bot::Phs(int y){
	if (y <= 20){
		Energy += 7 / (age * 0.001);
	}
	else if (y <= 40){
		Energy += 5 / (age * 0.001);
	}
	else{
		Energy += 2 / (age * 0.001);
	}
	PhsCount++;
}

void Bot::DoCommand(int x, int y, Bot **bots, int width, int height){
	if (cmds[turn] >= 1 && cmds[turn] <= 3){
		Phs(y);
	}
	else if (cmds[turn] == 4){
		Replicate(x, y, bots, width, height);
	}
	else if (cmds[turn] == 5){
		Eat(x, y, bots, width, height);
	}
	else if (cmds[turn] == 6){
		Move(x, y, bots, width, height);
	}
	else if (cmds[turn] == 7){
		Share(x, y, bots, width, height);
	}
	else if (cmds[turn] == 100){
		Cough(x, y, bots);
		std::cout << "100";
	}
	turn++;
	if (turn > 63){
		turn = 0;
	}
	Energy -= 3;
	age++;
}

void Bot::Replicate(int x, int y, Bot **bots, int width, int height){
	Bot NewBot;
	NewBot.Setup(cmds, true, DefaultEnergy, 0);
	NewBot.Infected = Infected;
	Replications++;
	if (Replications >= 4){
		NewBot.Mutate();
		Replications = 0;
	}
	if (x > 0 && !bots[x - 1][y].Exists){
		bots[x - 1][y] = NewBot;
	}
	else if (y > 0 && !bots[x][y - 1].Exists){
		bots[x][y - 1] = NewBot;
	}
	else if (x < width - 1 && !bots[x + 1][y].Exists){
		bots[x + 1][y] = NewBot;
	}
	else if (y < height - 1 && !bots[x][y + 1].Exists){
		bots[x][y + 1] = NewBot;
	}
	else{
		Alive = false;
	}
	Energy -= 20;
	if (Energy <= 0){
		Alive = false;
	}
}

std::string Bot::GetGen(){
	std::string dna;
	dna += "[";
	for (int x = 0; x != 64; x++){
		dna += std::to_string(cmds[x]) + ", ";
	}
	dna += "]";
	return dna;
}

void Bot::Eat(int x, int y, Bot **bots, int width, int height){
	int direction = cmds[turn + 1] % 4;
	switch (direction){
		case 0:
			if (y > 0 && bots[x][y - 1].Exists){
				bots[x][y - 1].Exists = false;
				Energy += bots[x][y - 1].GetEnergy();
				EatCount++;
			}
			break;
		case 1:
			if (x > 0 && bots[x - 1][y].Exists){
				bots[x - 1][y].Exists = false;
				Energy += bots[x - 1][y].GetEnergy();
				EatCount++;
				bots[x - 1][y].SetEnergy(0);
			}
			break;
		case 2:
			if (y < height - 1 && bots[x][y + 1].Exists){
				bots[y][x + 1].Exists = false;
				Energy += bots[y][x + 1].GetEnergy() + 50;
				bots[y][x + 1].SetEnergy(0);
				EatCount++;
			}
			break;
		case 3:
			if (x < width - 1 && bots[x + 1][y].Exists){
				bots[x + 1][y].Exists = false;
				EatCount++;
				Energy += bots[y + 1][y].GetEnergy();
				bots[x + 1][y].SetEnergy(0);
			}
			break;
		default:
			if (y > 0 && bots[x][y - 1].Exists){
				bots[x][y - 1].Exists = false;
				EatCount++;
				Energy += bots[x][y - 1].GetEnergy();
				bots[x][y - 1].SetEnergy(0);
			}
			break;
	}
}

void Bot::Move(int x, int y, Bot **bots, int width, int height){
	Bot MovedBot;
	MovedBot.Setup(cmds, true, Energy, age);
	MovedBot.PhsCount = PhsCount;
	MovedBot.EatCount = EatCount;
	MovedBot.Infected = Infected;
	MovedBot.Immunity = Immunity;
	int direction = cmds[turn + 1] % 4;
	switch (direction){
		case 1:
			if (y > 0 && !bots[x][y - 1].Exists){
				bots[x][y - 1] = MovedBot;
			}
			else if (!bots[x][height - 1].Exists){
				bots[x][0] = MovedBot;
			}
			else{
				return;
			}
			break;
		case 2:
			if (x > 0 && !bots[x - 1][y].Exists){
				bots[x - 1][y] = MovedBot;
			}
			else if (!bots[width - 1][y].Exists){
				bots[width - 1][y] = MovedBot;
			}
			else{
				return;
			}
		case 3:
			if (y < height - 1 && !bots[x][y + 1].Exists){
				bots[x][y + 1] = MovedBot;
			}
			else if (!bots[x][0].Exists){
				bots[x][0] = MovedBot;
			}
			else{
				return;
			}
			break;
		case 4:
			if (x < height - 1 && !bots[x + 1][y].Exists){
				bots[x + 1][y] = MovedBot;
			}
			else if (!bots[0][y].Exists){
				bots[0][y] = MovedBot;
			}
			else{
				return;
			}
			break;
		default:
			if (y > 0 && !bots[x][y - 1].Exists){
				bots[x][y - 1] = MovedBot;
			}
			else if (!bots[x][height - 1].Exists){
				bots[x][height - 1] = MovedBot;
			}
			else{
				return;
			}
			break;
	}
	Bot EmptyBot;
	EmptyBot.Setup(cmds, false, 200, 0);
	bots[x][y] = EmptyBot;
}

void Bot::Share(int x, int y, Bot **bots, int width, int height){
	int direction = cmds[turn + 1] % 4;
	int amount = cmds[turn + 2];
	amount = amount * 5;
	if (y > 0 && direction == 0 && bots[x][y - 1].Alive){
		bots[x][y - 1].GiveEnergy(amount);
	}
	else if (x > 0 && direction == 1 && bots[x - 1][y].Alive){
		bots[x - 1][y].GiveEnergy(amount);
	}
	else if (y < height - 1 && direction == 2 && bots[x][y + 1].Alive){
		bots[x][y + 1].GiveEnergy(amount);
	}
	else if (x < width - 1 && direction == 3 && bots[x + 1][y].Alive){
		bots[x + 1][y].GiveEnergy(amount);
	}
	else{
		return;
	}
	Energy -= amount;
}

void Bot::GiveEnergy(int amount){
	Energy += amount * 8;
}

void Bot::Mutate(){
	srand(time(0));
	int DNAindex = rand() % 64;
	cmds[DNAindex] = rand() % 7 + 1;
	Replications = 0;
}

void Bot::Cough(int x, int y, Bot **bots){ // Infect bots in all directions
	int SetInfect = rand() % 100; // Get infect chance
	int CmdNum = rand() % 64; // Get cmd num for infect
	if (x > 0 && bots[y][x - 1].Alive && SetInfect < InfectChance && !bots[y][x - 1].Immunity){
		bots[y][x - 1].Infected = true;
		bots[y][x - 1].ChangeGen(CmdNum, 100);
	}
	SetInfect = rand() % 100;
	CmdNum = rand() % 64;
	if (y > 0 && bots[y - 1][x].Alive && SetInfect < InfectChance && !bots[y - 1][x].Immunity){
		bots[y - 1][x].Infected = true;
		bots[y - 1][x].ChangeGen(CmdNum, 100);
	}
	SetInfect = rand() % 100;
	CmdNum = rand() % 64;
	if (x < 99 && bots[y][x + 1].Alive && SetInfect < InfectChance && !bots[y][x + 1].Immunity){
		bots[y][x + 1].Infected = true;
		bots[y][x + 1].ChangeGen(CmdNum, 100);
	}
	SetInfect = rand() % 100;
	CmdNum = rand() % 64;
	if (y < 59 && bots[y + 1][x].Alive && SetInfect < InfectChance && !bots[y + 1][x].Immunity){
		bots[y + 1][x].Infected = true;
		bots[y + 1][x].ChangeGen(CmdNum, 100);
	}
}


void Bot::ChangeGen(int cmdNum, int value){
	cmds[cmdNum] = value;
}
