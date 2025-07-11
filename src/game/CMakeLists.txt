
add_library(game STATIC
	win.hpp
	win.cpp
	game.hpp
	game.cpp
	canvas.hpp
	canvas.cpp
)

target_link_libraries(game glfw webgpu)
