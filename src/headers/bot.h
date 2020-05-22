#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

class Bot{
public:
	Bot();
	void Setup(int cmd[64], bool exst, int AmEnergy, int age = 0);
	void DoCommand(int x, int y, Bot bots[60][100]);
	int GetEnergy() { return Energy; }
	void SetEnergy(int En) { Energy = En; }
	int GetRepl() { return Replications; }
	void GiveEnergy(int amount);
	std::string GetGen();
	bool Exists;
	bool Alive = true;
	void Mutate();
	int PhsCount = 1;
	int EatCount = 0;
	bool Infected = false;
	bool Immunity = false;
	void ChangeGen(int cmdNum, int value);
private:
	int age = 0;
	int cmds[64];
	int Energy = 1000;
	int turn = 0;
	int Replications = 0;
	void Phs(int y);
	void Replicate(int x, int y, Bot bots[60][100]);
	void Eat(int x, int y, Bot bots[60][100]);
	void Move(int x, int y, Bot bots[60][100]);
	void Share(int x, int y, Bot bots[60][100]);
	void Cough(int x, int y, Bot bots[60][100]);
	int DefaultEnergy = 1000;
	int InfectChance = 30;
};