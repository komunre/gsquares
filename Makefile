LIBS = -lsfml-graphics -lsfml-window -lsfml-system

%.o: src/%.cpp
	g++ -c -o $@ $< $(LIBS)

%.o: src/headers/%.cpp
	g++ -c -o $@ $< $(LIBS)

build: src/main.o src/headers/bot.o src/headers/field.o
	g++ src/main.o src/headers/bot.o src/headers/field.o -o gsquares $(LIBS)
all: build
