
#include <iostream>
#include <GLFW/glfw3.h>
#include <glfw3webgpu.h>

#include "cosmos.hpp"
#include "game/game.hpp"

int main(int argc, const char* argv)
{
	Game game;

	game.init();

	while (game.tick()) {
	}


	game.finit();
}
