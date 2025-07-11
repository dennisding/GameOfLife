
#include "win.hpp"

Win::Win() : width_(0), height_(0), window_(nullptr)
{

}

Win::~Win()
{
	if (window_) {
		glfwDestroyWindow(window_);
		window_ = nullptr;
	}
}

bool Win::init(int width, int height, const std::string& title)
{
	width_ = width;
	height_ = height;
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	return true;
}

bool Win::tick()
{
	if (glfwWindowShouldClose(window_)) {
		return false;
	}

	glfwPollEvents();
	return true;
}

void Win::finit()
{

}