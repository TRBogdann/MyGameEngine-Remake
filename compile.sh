g++ -o program1 $1 \
    graphics_engine/window/window.cpp \
    graphics_engine/program/program.cpp \
    math_engine/math.cpp \
    graphics_engine/buffers/buffers.cpp \
    graphics_engine/shaders/shader.cpp \
    graphics_engine/texture/texture.cpp \
    graphics_engine/renderer/renderer.cpp \
    graphics_engine/transformations/transformations.cpp \
    graphics_engine/camera/camera.cpp \
    -lEGL -lOpenGL $(pkg-config --cflags --libs glew glfw3) 