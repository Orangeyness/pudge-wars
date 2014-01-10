set(ENGINE_FILES 
	GameEngine.cpp 
	GameException.cpp 
	GameEntityInterface.cpp
	EntityPool.cpp 
	GeometryHelper.cpp 
	Observer.cpp 
	CollidableEntityInterface.cpp
	EventWithEntity.cpp
	)

add_library (EngineCore ${ENGINE_FILES})
target_link_libraries(EngineCore ${ALLEGRO_LIBRARIES})
