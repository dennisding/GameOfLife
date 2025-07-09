
add_library(GameOfLifeLib STATIC
	cosmos.cpp
	cosmos_builder.cpp

	allocator.hpp
	config.hpp
	cosmos.hpp
	cosmos_builder.hpp
	life.hpp
)

target_include_directories(GameOfLifeLib PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE GameOfLifeLib)

add_executable(GameOfLifeGui wgpu_main.cpp)
target_link_libraries(GameOfLifeGui PRIVATE webgpu)
target_link_libraries(GameOfLifeGui PRIVATE GameOfLifeLib)
target_copy_webgpu_binaries(GameOfLifeGui)