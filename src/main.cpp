#include <iostream>
#include <cstdlib>
#include <fstream>
#include "headers/field.h"


using namespace std;

void CreateBotForField(Field &f){
	int cmds[64];
	cmds[0] = 2;
	for (int x = 1; x != 64; x++){
		cmds[x] = rand() % 7 + 1;
	}
	cout << "Commands created. Creating bot..." << endl;
	Bot CreateBot;
	cout << "Bot created. Getting DNA..." << endl;
	string DNA = CreateBot.GetGen();
	cout << DNA << endl;
	CreateBot.Setup(cmds, true, 1000, 0);
	ofstream DNAlog("DNA.txt", ios::app);
	DNAlog << DNA << endl;
	DNAlog.close();
	f.AddBot(rand() % 60, rand() % 100, CreateBot);
}

int main(int argc, char* argv[]){
	srand(time(0));
	cout << "Main function is working." << endl;
	int sleepMs = 0;
	if (argc > 1){
		sleepMs = atoi(argv[1]);
	}
	Field allf(sleepMs);
	CreateBotForField(allf);
	CreateBotForField(allf);
	sf::RenderWindow window(sf::VideoMode(1200, 700), "ALife");
	while (window.isOpen()){
		window.clear(sf::Color::Black);
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		allf.ExecuteAllCmds();
		allf.Draw(window);
		window.display();
	}
}
