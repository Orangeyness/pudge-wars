# Based on build script from
# http://stackoverflow.com/questions/9689183/cmake-googletest/9695234#9695234

cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(Test)

# Create patch file for gtest with MSVC 2012
if(MSVC_VERSION EQUAL 1700)
  file(WRITE ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "Index: cmake/internal_utils.cmake\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "===================================================================\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "--- cmake/internal_utils.cmake   (revision 660)\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "+++ cmake/internal_utils.cmake   (working copy)\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "@@ -66,6 +66,9 @@\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "       # Resolved overload was found by argument-dependent lookup.\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "       set(cxx_base_flags \"\${cxx_base_flags} -wd4675\")\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "     endif()\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "+    if (MSVC_VERSION EQUAL 1700)\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "+      set(cxx_base_flags \"\${cxx_base_flags} -D_VARIADIC_MAX=10\")\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "+    endif ()\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "     set(cxx_base_flags \"\${cxx_base_flags} -D_UNICODE -DUNICODE -DWIN32 -D_WIN32\")\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "     set(cxx_base_flags \"\${cxx_base_flags} -DSTRICT -DWIN32_LEAN_AND_MEAN\")\n")
  file(APPEND ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "     set(cxx_exception_flags \"-EHsc -D_HAS_EXCEPTIONS=1\")\n")
else()
  file(WRITE ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch "")
endif()

# Enable ExternalProject CMake module
include(ExternalProject)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)

# Add gtest
ExternalProject_Add(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    SVN_REVISION -r 671
    TIMEOUT 10
    PATCH_COMMAND svn patch ${CMAKE_BINARY_DIR}/ThirdParty/gtest.patch ${CMAKE_BINARY_DIR}/ThirdParty/src/googletest
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Add compiler flag for MSVC 2012
if(MSVC_VERSION EQUAL 1700)
  add_definitions(-D_VARIADIC_MAX=10)
endif()

add_subdirectory (core)
add_subdirectory (${GAME_FILE_DIRECTORY})

# Add test executable target
add_executable(TestEngine main.cpp $<TARGET_OBJECTS:EngineCoreTest>)
add_executable(Test${CMAKE_PROJECT_NAME} main.cpp $<TARGET_OBJECTS:GameComponentsTest>)

# Create dependency of MainTest on googletest
add_dependencies(TestEngine googletest)
add_dependencies(Test${CMAKE_PROJECT_NAME} googletest)

# Specify MainTest's link libraries
ExternalProject_Get_Property(googletest binary_dir)
if(MSVC)
  set(Suffix ".lib")
else()
  set(Suffix ".a")
  set(Pthread "-pthread")
endif()

target_link_libraries(
    TestEngine
	${ALLEGRO_LIBRARIES}
    debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})
target_link_libraries(
    Test${CMAKE_PROJECT_NAME}
	${ALLEGRO_LIBRARIES}
    debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})
