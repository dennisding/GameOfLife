
add_library(GameOfLifeLib STATIC
	cosmos.hpp cosmos.cpp
	cosmos_builder.hpp cosmos_builder.cpp
	allocator.hpp
	config.hpp
	life.hpp
	thread_pool.hpp thread_pool.cpp
)
target_include_directories(GameOfLifeLib PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(wgpu)
add_subdirectory(game)

# game of life
add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE GameOfLifeLib)

# game of life teset
add_executable(GameOfLifeTest test_main.cpp)
target_link_libraries(GameOfLifeTest PRIVATE GameOfLifeLib)

# game of life gui
add_executable(GameOfLifeGui wgpu_main.cpp)
target_link_libraries(GameOfLifeGui PRIVATE 
	GameOfLifeLib 
	game
	webgpu 
	wgpu
	glfw
	glfw3webgpu
)
target_copy_webgpu_binaries(GameOfLifeGui)