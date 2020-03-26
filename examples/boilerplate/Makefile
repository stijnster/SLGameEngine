all: prepare clean build run

run:
	LD_LIBRARY_PATH=/usr/local/lib/ bin/game

clean: prepare
	rm -rf tmp/* bin/*

build: main.o SL_GameEngine.o SL_TextureManager.o SL_GameObject.o
	g++ tmp/*.o -o bin/game -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -c main.cpp -o tmp/main.o -I../../lib

SL_GameEngine.o:
	g++ -c ../../lib/SL_GameEngine.cpp -o tmp/SL_GameEngine.o

SL_GameObject.o:
	g++ -c ../../lib/SL_GameObject.cpp -o tmp/SL_GameObject.o

SL_TextureManager.o:
	g++ -c ../../lib/SL_TextureManager.cpp -o tmp/SL_TextureManager.o

prepare:
	if [ ! -d "tmp" ]; then mkdir "tmp"; fi
	if [ ! -d "bin" ]; then mkdir "bin"; fi