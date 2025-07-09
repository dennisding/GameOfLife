
#include "cosmos.hpp"

#include <webgpu/webgpu.hpp>
#include <iostream>

int main(int argc, const char* argv)
{
	WGPUInstanceDescriptor desc = {};
	desc.nextInChain = nullptr;

	WGPUInstance instance = wgpuCreateInstance(&desc);
	if (!instance) {
		return 1;
	}
}
