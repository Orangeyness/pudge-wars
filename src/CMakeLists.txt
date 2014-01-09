add_subdirectory (core)
add_subdirectory (${GAME_FILE_DIRECTORY})

add_executable(${CMAKE_PROJECT_NAME} main.cpp $<TARGET_OBJECTS:gameComponents>)
target_link_libraries(${CMAKE_PROJECT_NAME} EngineCore ${ALLEGRO_LIBRARIES})
