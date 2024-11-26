cmake_minimum_required(VERSION 3.10)
project(main.exe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.c src/foxcore/render.c src/foxcore/shader.c src/foxcore/io.c src/foxcore/glad/glad.c)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main m)
