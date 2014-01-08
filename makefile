#Settings
CPP = g++ -std=c++11
CFLAGS = -g -Wall
CLIBS = `pkg-config --libs allegro-5 allegro_primitives-5`

default: game

game: main.o GameEngine.o GameException.o EntityPool.o GeometryHelper.o IntroState.o PudgeEntity.o UserInputProxy.o
	$(CPP) $(CFLAGS) -o hookgame main.o GameEngine.o GameException.o EntityPool.o GeometryHelper.o IntroState.o PudgeEntity.o UserInputProxy.o $(CLIBS) 

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp

GameEngine.o : GameEngine.cpp GameEngine.h GameException.h GameStateInterface.h
	$(CPP) $(CFLAGS) -c GameEngine.cpp

GameException.o : GameException.cpp GameException.h ExceptionIds.h
	$(CPP) $(CFLAGS) -c GameException.cpp

EntityPool.o : EntityPool.cpp EntityPool.h
	$(CPP) $(CFLAGS) -c EntityPool.cpp

GeometryHelper.o : GeometryHelper.cpp GeometryHelper.h
	$(CPP) $(CFLAGS) -c GeometryHelper.cpp

IntroState.o : IntroState.cpp IntroState.h GameStateInterface.h
	$(CPP) $(CFLAGS) -c IntroState.cpp

PudgeEntity.o : PudgeEntity.cpp PudgeEntity.h GameEntityInterface.h
	$(CPP) $(CFLAGS) -c PudgeEntity.cpp

UserInputProxy.o : UserInputProxy.cpp UserInputProxy.h InputProxyInterface.h
	$(CPP) $(CFLAGS) -c UserInputProxy.cpp

clean :
	rm hookgame *.o *~
