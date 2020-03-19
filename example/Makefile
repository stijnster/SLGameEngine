all: game

game: main.o engine.o
	g++ tmp/main.o tmp/engine.o -o bin/game

main.o: main.cpp
	g++ -c main.cpp -o tmp/main.o

engine.o:
	g++ -c ../lib/SL_GameEngine.cpp -o tmp/engine.o

clean:
	rm -rf *.o game