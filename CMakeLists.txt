cmake_minimum_required(VERSION 3.9)
project(main)

# Setup libraries
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)

FetchContent_MakeAvailable(raylib)

# Setup executable
add_executable(${PROJECT_NAME} "src/main.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
