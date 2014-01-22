include_directories("${CMAKE_SOURCE_DIR}/include/pudge-wars")

set(GAME_FILES 
	IntroState.cpp 
	ViewPort.cpp
	UserInputProxy.cpp
	HookableInterface.cpp
	WallEntity.cpp
	BallEntity.cpp
	HookEntity.cpp
	PudgeEntity.cpp 
	pudge-states/PudgeState.cpp
	pudge-states/PudgeWalkState.cpp
	pudge-states/PudgeHookThrowState.cpp
	pudge-states/PudgeStunRecoveryState.cpp
	pudge-states/PudgeOnHookState.cpp
	)

add_library(GameComponents OBJECT ${GAME_FILES})
