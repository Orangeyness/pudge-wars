set(ENGINE_FILES 
	GameEngine.cpp 
	GameConstants.cpp
	GameException.cpp 
	GameDebugWindow.cpp
	services/ServiceLocator.cpp
	events/Event.cpp
	events/EventArgs.cpp
	events/BufferedEventService.cpp
	events/EventObserver.cpp
	entities/EntityManager.cpp
	entities/Entity.cpp
	entities/EntityCollidable.cpp
	entities/EntityBoundingBox.cpp
	entities/EntityRadial.cpp
	helpers/GeometryHelper.cpp
	helpers/CollisionHelper.cpp
	)

add_library(EngineCore OBJECT ${ENGINE_FILES})
