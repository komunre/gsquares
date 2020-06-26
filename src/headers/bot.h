#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

class Bot{
public:
	Bot();
	void Setup(int cmd[64], bool exst, int AmEnerg, int age);
	void DoCommand(int x, int y, Bot **bots, int weidth, int height);
	int GetEnergy() { return Energy; }
	void SetEnergy(int En) { Energy = En; }
	int GetRepl() { return Replications; }
	void GiveEnergy(int amount);
	std::string GetGen();
	bool Exists; //Anyway Bot exists in array but if bo doesn't exists he does'nt drawing and commands not exected
	bool Alive = true;
	void Mutate();
	int PhsCount = 1; //For color
	int EatCount = 0; //For color
	bool Infected = false;
	bool Immunity = false;
	void ChangeGen(int cmdNum, int value);
private:
	int age = 0;
	int cmds[64]; //commands for execution
	int Energy = 1000; //Energy for ations
	int turn = 0; //Current command num
	int Replications = 0; //Replications counter for mutations
	void Phs(int y);
	void Replicate(int x, int y, Bot **bots, int width, int height);
	void Eat(int x, int y, Bot **bots, int width, int height);
	void Move(int x, int y, Bot **bots, int width, int height);
	void Share(int x, int y, Bot **bots, int width, int height);
	void Cough(int x, int y, Bot **bots, int width, int height);
	int DefaultEnergy = 1000; //Enegy gived after birth
	int InfectChance = 30;
};
