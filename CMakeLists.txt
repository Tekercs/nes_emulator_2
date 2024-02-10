cmake_minimum_required(VERSION 3.18)
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
