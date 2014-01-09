set(ENGINE_FILES GameEngine.cpp GameException.cpp EntityPool.cpp GeometryHelper.cpp)

add_library (EngineCore ${ENGINE_FILES})
target_link_libraries(EngineCore ${ALLEGRO_LIBRARIES})
