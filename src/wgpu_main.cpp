
#include "cosmos.hpp"

// #include <webgpu/webgpu.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, const char* argv)
{
	//WGPUInstanceDescriptor desc = {};
	//desc.nextInChain = nullptr;

	//WGPUInstance instance = wgpuCreateInstance(&desc);
	//if (!instance) {
	//	return 1;
	//}

	//std::cout << "webgpu inited:" << instance << std::endl;

	//wgpuInstanceRelease(instance);

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // <-- extra info for glfwCreateWindow
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Game Of Life", nullptr, nullptr);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

}
