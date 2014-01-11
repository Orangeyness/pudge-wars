set(GAME_TEST_FILES UserInputProxyTest.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/${GAME_FILE_DIRECTORY}/)

add_library(GameComponentsTest OBJECT ${GAME_TEST_FILES})
add_dependencies(EngineCoreTest googleTest)
