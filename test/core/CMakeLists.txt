set(ENGINE_TEST_FILES GameEngineTest.cpp GeometryHelperTest.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/core/)

add_library(EngineCoreTest OBJECT ${ENGINE_TEST_FILES})
add_dependencies(EngineCoreTest googleTest)
