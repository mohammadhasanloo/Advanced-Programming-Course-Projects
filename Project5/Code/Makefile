SDL_FLAGS = -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out

soccerStars.out: main.o rsdl.o Game.o Player.o Bead.o Ball.o
	g++ -std=c++11 main.o rsdl.o Game.o Player.o Bead.o Ball.o ${SDL_FLAGS} -o soccerStars.out

main.o: main.cpp rsdl.hpp Game.hpp Player.hpp Ball.hpp Bead.hpp Const_Values.hpp
	g++ -std=c++11 -c main.cpp ${SDL_FLAGS} -o main.o

Game.o: Game.cpp rsdl.hpp Player.hpp Ball.hpp Bead.hpp Const_Values.hpp
	g++ -std=c++11 -c Game.cpp ${SDL_FLAGS} -o Game.o


Bead.o: Bead.cpp rsdl.hpp Ball.hpp Const_Values.hpp
	g++ -std=c++11 -c Bead.cpp ${SDL_FLAGS} -o Bead.o


Ball.o: Ball.cpp rsdl.hpp Const_Values.hpp
	g++ -std=c++11 -c Ball.cpp ${SDL_FLAGS} -o Ball.o


Player.o: Player.cpp rsdl.hpp Const_Values.hpp
	g++ -std=c++11 -c Player.cpp ${SDL_FLAGS} -o Player.o

rsdl.o: rsdl.cpp
	g++ -std=c++11 -c rsdl.cpp ${SDL_FLAGS} -o rsdl.o
clean:
	rm *.o soccerStars.out
