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

private:
	GLFWwindow* window_;
};

using WinPtr = std::shared_ptr<Win>;