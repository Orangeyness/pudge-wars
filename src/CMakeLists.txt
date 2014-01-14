add_subdirectory (core)
add_subdirectory (${GAME_FILE_DIRECTORY})

add_executable(${CMAKE_PROJECT_NAME} main.cpp $<TARGET_OBJECTS:GameComponents> $<TARGET_OBJECTS:EngineCore>)
target_link_libraries(${CMAKE_PROJECT_NAME} ${ALLEGRO_LIBRARIES})
