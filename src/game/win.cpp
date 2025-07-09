
#include "win.hpp"

Win::Win() : window_(nullptr)
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
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window_ = glfwCreateWindow(1024, 768, title.c_str(), nullptr, nullptr);

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