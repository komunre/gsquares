#include "bot.h"

Bot::Bot(){}

void Bot::Setup(int cmd[64], bool exst, int AmEnergy){
	for (int x = 0; x != 64; x++){
		cmds[x] = cmd[x];
	}
	Exists = exst;
	Energy = AmEnergy;
}

void Bot::Phs(int y){
	if (y <= 20){
		Energy += 7;
	}
	else if (y <= 40){
		Energy += 5;
	}
	else{
		Energy += 2;
	}
	PhsCount++;
}

void Bot::DoCommand(int x, int y, Bot bots[60][100]){
	if (cmds[turn] >= 1 && cmds[turn] <= 3){
		Phs(y);
	}
	else if (cmds[turn] == 4){
		Replicate(x, y, bots);
	}
	else if (cmds[turn] == 5){
		Eat(x, y, bots);
	}
	else if (cmds[turn] == 6){
		Move(x, y, bots);
	}
	else if (cmds[turn] == 7){
		Share(x, y, bots);
	}
	turn++;
	if (turn > 63){
		turn = 0;
	}
	Energy -= 3;
}

void Bot::Replicate(int x, int y, Bot bots[60][100]){
	Bot NewBot;
	NewBot.Setup(cmds, true, DefaultEnergy);
	Replications++;
	if (Replications >= 4){
		NewBot.Mutate();
		Replications = 0;
	}
	if (y > 0 && !bots[y - 1][x].Exists){
		bots[y - 1][x] = NewBot;
	}
	else if (!bots[59][x].Exists){
		bots[y][99] = NewBot;
		return;
	}
	if (x > 0 && !bots[y][x - 1].Exists){
		bots[y][x - 1] = NewBot;
	}
	else if (!bots[y][99].Exists){
		bots[y][99] = NewBot;
		return;
	}
	if (y < 59 && !bots[y + 1][x].Exists){
		bots[y + 1][x] = NewBot;
	}
	else if (!bots[0][x].Exists){
		bots[0][x] = NewBot;
		return;
	}
	if (x < 99 && !bots[y][x + 1].Exists){
		bots[y][x + 1] = NewBot;
	}
	else if (!bots[y][0].Exists){
		bots[y][0] = NewBot;
		return;
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

void Bot::Eat(int x, int y, Bot bots[60][100]){
	int direction = cmds[turn + 1] % 4;
	switch (direction){
		case 0:
			if (x > 0 && bots[y][x - 1].Exists){
				bots[y][x - 1].Exists = false;
				Energy += bots[y][x - 1].GetEnergy();
				EatCount++;
			}
			break;
		case 1:
			if (y > 0 && bots[y - 1][x].Exists){
				bots[y - 1][x].Exists = false;
				Energy += bots[y - 1][x].GetEnergy();
				EatCount++;
				bots[y - 1][x].SetEnergy(0);
			}
			break;
		case 2:
			if (x < 99 && bots[y][x + 1].Exists){
				bots[y][x + 1].Exists = false;
				Energy += bots[y][x + 1].GetEnergy();
				bots[y][x + 1].SetEnergy(0);
				EatCount++;
			}
			break;
		case 3:
			if (y < 59 && bots[y + 1][x].Exists){
				bots[y + 1][x].Exists = false;
				EatCount++;
				Energy += bots[y + 1][x].GetEnergy();
				bots[y + 1][x].SetEnergy(0);
			}
			break;
		default:
			if (x > 0 && bots[y][x - 1].Exists){
				bots[y][x - 1].Exists = false;
				EatCount++;
				Energy += bots[y][x - 1].GetEnergy();
				bots[y][x - 1].SetEnergy(0);
			}
			break;
	}
}

void Bot::Move(int x, int y, Bot bots[60][100]){
	Bot MovedBot;
	MovedBot.Setup(cmds, true, Energy);
	MovedBot.PhsCount = PhsCount;
	MovedBot.EatCount = EatCount;
	int direction = cmds[turn + 1] % 4;
	switch (direction){
		case 1:
			if (x > 0 && !bots[y][x - 1].Exists){
				bots[y][x - 1] = MovedBot;
			}
			else if (!bots[y][99].Exists){
				bots[y][99] = MovedBot;
			}
			else{
				return;
			}
			break;
		case 2:
			if (y > 0 && !bots[y - 1][x].Exists){
				bots[y - 1][x] = MovedBot;
			}
			else if (!bots[59][x].Exists){
				bots[59][x] = MovedBot;
			}
			else{
				return;
			}
		case 3:
			if (x < 99 && !bots[y][x + 1].Exists){
				bots[y][x + 1] = MovedBot;
			}
			else if (!bots[y][0].Exists){
				bots[y][0] = MovedBot;
			}
			else{
				return;
			}
			break;
		case 4:
			if (y < 59 && !bots[y + 1][x].Exists){
				bots[y + 1][x] = MovedBot;
			}
			else if (!bots[0][x].Exists){
				bots[0][x] = MovedBot;
			}
			else{
				return;
			}
			break;
		default:
			if (x > 0 && !bots[y][x - 1].Exists){
				bots[y][x - 1] = MovedBot;
			}
			else if (!bots[y][99].Exists){
				bots[y][99] = MovedBot;
			}
			else{
				return;
			}
			break;
	}
	Bot EmptyBot;
	EmptyBot.Setup(cmds, false, 200);
	bots[y][x] = EmptyBot;
}

void Bot::Share(int x, int y, Bot bots[60][100]){
	int direction = cmds[turn + 1] % 4;
	int amount = cmds[turn + 2];
	amount = amount * 5;
	if (x > 0 && direction == 0 && bots[y][x - 1].Alive){
		bots[y][x - 1].GiveEnergy(amount);
	}
	else if (y > 0 && direction == 1 && bots[y - 1][x].Alive){
		bots[y - 1][x].GiveEnergy(amount);
	}
	else if (x < 99 && direction == 2 && bots[y][x + 1].Alive){
		bots[y][x + 1].GiveEnergy(amount);
	}
	else if (y < 59 && direction == 3 && bots[y + 1][x].Alive){
		bots[y + 1][x].GiveEnergy(amount);
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