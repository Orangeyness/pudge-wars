#Settings
CPP = g++ -std=c++11
CFLAGS = -g -Wall
CLIBS = `pkg-config --libs allegro-5 allegro_primitives-5`

default: game

game: main.o GameEngine.o GameException.o IntroState.o
	$(CPP) $(CFLAGS) -o hookgame main.o GameEngine.o GameException.o IntroState.o $(CLIBS) 

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp

GameEngine.o : GameEngine.cpp GameEngine.h GameException.h GameStateInterface.h
	$(CPP) $(CFLAGS) -c GameEngine.cpp

GameException.o : GameException.cpp GameException.h ExceptionIds.h
	$(CPP) $(CFLAGS) -c GameException.cpp

IntroState.o : IntroState.cpp IntroState.h GameStateInterface.h
	$(CPP) $(CFLAGS) -c IntroState.cpp

clean :
	rm hookgame *.o *~
