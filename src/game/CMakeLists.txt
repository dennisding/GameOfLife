
add_library(game STATIC
	win.hpp
	win.cpp
	game.hpp
	game.cpp
)

target_link_libraries(game glfw webgpu)
