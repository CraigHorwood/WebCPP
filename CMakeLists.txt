cmake_minimum_required(VERSION 3.0.0)
project(WebCPP VERSION 0.1.0 LANGUAGES C CXX)

FILE(GLOB SOURCE_FILES src/*.cpp src/graphics/*.cpp src/state/*.cpp src/level/*.cpp src/entity/*.cpp)
FILE(COPY assets DESTINATION .)

add_executable(WebCPP
	${SOURCE_FILES}
	external_modules/lodepng/lodepng.cpp
)

include_directories(external_modules/lodepng)

# Link GLFW3

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external_modules/glfw)
target_link_libraries(WebCPP glfw)

# Static link GLEW

add_subdirectory(external_modules/glew)
target_link_libraries(WebCPP libglew_static)

# Static link lodepng

# add_library(lodepng STATIC external_modules/lodepng/lodepng.cpp external_modules/lodepng/lodepng.h)
# target_include_directories(WebCPP PUBLIC external_modules/lodepng)