
add_library(wgpu STATIC
	wadapter.hpp
	wadapter.cpp
	wdevice.hpp
	wdevice.cpp
)

target_link_libraries(wgpu webgpu)
