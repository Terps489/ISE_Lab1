cmake_minimum_required(VERSION 3.10)

project(test_file)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} project/project.cpp)

add_custom_target(run ALL
    COMMAND ./${PROJECT_NAME}
    COMMAND rm -rf ${PROJECT_NAME}
)

add_custom_target(clear
    COMMAND rm -rf build/* CMakeCache.txt *.cmake Makefile CMakeFiles/
    COMMAND echo "Build directory cleaned!"
)

add_custom_target(git
    COMMAND git add .
    COMMAND git commit -m "CMake auto-commit: ${PROJECT_NAME} build"
    COMMAND git push origin develop
)