
add_library(game STATIC
	win.hpp	win.cpp
	game.hpp game.cpp
	world.hpp world.cpp
	visual_life.hpp visual_life.cpp
	time_controller.hpp time_controller.cpp
	gui.hpp gui.cpp
	view_port.hpp view_port.cpp
	game_system.hpp game_system.cpp
	rectangle.hpp rectangle.cpp
	color.hpp color.cpp
	position.hpp position.cpp
	input.hpp input.cpp
	button.hpp button.cpp
	render_set.hpp render_set.cpp
)

target_link_libraries(game glfw webgpu)
