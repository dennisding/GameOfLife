#pragma once

#include "input.hpp"

#include <GLFW/glfw3.h>

#include <string>
#include <memory>

class Game;

class Win
{
public:
	Win(Game* game);
	~Win();

	bool init(int width, int height, const std::string &title);
	void pre_tick();
	bool tick();
	void finit();

	inline int width() { return width_;  }
	inline int height() { return height_; }

private:
	int width_;
	int height_;

public:
	// internal use
	Game* game_;
	GLFWwindow* window_;
	InputPtr input_;
};

using WinPtr = std::shared_ptr<Win>;