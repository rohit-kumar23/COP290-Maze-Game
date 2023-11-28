all: maze
	g++ Game.o main.o -o yourcode.out -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


maze: Game.cpp main.cpp
	g++ -L/usr/include/x86_64-linux-gnu/SDL2 -I/usr/include/SDL2 -c Game.cpp main.cpp


run:
	./yourcode.out



clean:
	rm *.out *.o
