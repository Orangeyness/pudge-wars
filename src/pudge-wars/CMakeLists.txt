set(GAME_FILES 
	IntroState.cpp 
	PudgeEntity.cpp 
	UserInputProxy.cpp
	WallEntity.cpp
	BallEntity.cpp
	)

add_library(GameComponents OBJECT ${GAME_FILES})
