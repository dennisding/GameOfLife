
add_library(wgpu STATIC
	wadapter.hpp wadapter.cpp
	wdevice.hpp wdevice.cpp
	wcommand.hpp wcommand.cpp
	wtexture.hpp wtexture.cpp
	wpipe_line.hpp wpipe_line.cpp
	wbuffer.hpp wbuffer.cpp
	wpipe_line_layout.hpp wpipe_line_layout.cpp
	wbind_group.hpp wbind_group.cpp
)

target_link_libraries(wgpu webgpu glfw glfw3webgpu)
