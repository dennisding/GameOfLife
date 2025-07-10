
cmake_minimum_required(VERSION 3.10)

project(GameOfLife CXX)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(glfw)
add_subdirectory(webgpu)
add_subdirectory(glfw3webgpu)

# add the source and project
add_subdirectory(src)
