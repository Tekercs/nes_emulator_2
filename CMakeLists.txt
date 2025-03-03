cmake_minimum_required(VERSION 3.18)
include(FetchContent)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
  GIT_TAG release-2.30.0
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY git@github.com:google/googletest
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest SDL3)

project(
	nesemu
	VERSION 0.1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

file(GLOB
	SRC_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
)

add_executable(
	${CMAKE_PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
	${SRC_FILES}
)

target_include_directories(
	${CMAKE_PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB
	UNIT_TESTS_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/test/**/*.cpp
)
add_executable(unit_tests ${UNIT_TESTS_SRC} ${SRC_FILES})

target_link_libraries(unit_tests gtest_main)
target_include_directories(
	unit_tests
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME unit_tests_ctest COMMAND unittests)
