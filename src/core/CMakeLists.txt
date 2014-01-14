set(ENGINE_FILES 
	GameEngine.cpp 
	GameConstants.cpp
	GameException.cpp 
	GameDebugWindow.cpp
	GameEntityInterface.cpp
	EntityPool.cpp 
	MessageRouter.cpp
	Observer.cpp 
	Event.cpp
	EventArgs.cpp
	GeometryHelper.cpp 
	CollidableEntityInterface.cpp
	BoundingBoxEntityInterface.cpp
	RadialEntityInterface.cpp
	CollisionChecker.cpp
	)

add_library(EngineCore OBJECT ${ENGINE_FILES})
