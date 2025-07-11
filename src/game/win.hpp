#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <memory>

class Win
{
public:
	Win();
	~Win();

	bool init(int width, int height, const std::string &title);
	bool tick();
	void finit();

	inline int width() { return width_;  }
	inline int height() { return height_; }

private:
	int width_;
	int height_;

public:
	// internal use
	GLFWwindow* window_;
};

using WinPtr = std::shared_ptr<Win>;