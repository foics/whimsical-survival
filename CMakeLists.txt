cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
link_directories(lib)

add_executable(${PROJECT_NAME} src/main.cpp src/foxcore/io.cpp src/foxcore/render.cpp src/foxcore/shader.cpp src/foxcore/parser.cpp src/foxcore/glad/glad.c)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 m)
