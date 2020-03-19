all: game

game: main.o SL_GameEngine.o SL_TextureManager.o
	g++ tmp/*.o -o bin/game -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -c main.cpp -o tmp/main.o -I../lib

SL_GameEngine.o:
	g++ -c ../lib/SL_GameEngine.cpp -o tmp/SL_GameEngine.o

SL_TextureManager.o:
	g++ -c ../lib/SL_TextureManager.cpp -o tmp/SL_TextureManager.o

clean:
	rm -rf tmp/* bin/*