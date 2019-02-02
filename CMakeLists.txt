cmake_minimum_required(VERSION 3.13)
project(ProjectSnake)

set(CMAKE_CXX_STANDARD 17)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL        OFF CACHE STRING "" FORCE)
add_subdirectory(thirdparty/glfw)
include_directories(thirdparty/glfw/include)

# GLEW
add_definitions(-DGLEW_STATIC)
option(glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory(thirdparty/glew)
include_directories(thirdparty/glew/include thirdparty/glew/src)

# GLM
include_directories(thirdparty/glm/glm)

# STB
include_directories(thirdparty/stb)

# imgui
include_directories(thirdparty/imgui)

# Google Test
add_subdirectory(thirdparty/gtest)
include_directories(thirdparty/gtest/googletest thirdparty/gtest/googlemock)

# assimp
add_subdirectory(thirdparty/assimp/)
include_directories(thirdparty/assimp/include thirdparty/assimp/code)

# nlohman_json
include_directories(thirdparty/nlohman_json/single_include)

file(GLOB_RECURSE HEADER_FILES include)
include_directories(include)

# Main Executable
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB IMGUI_FILES thirdparty/imgui/*.h thirdparty/imgui/*.cpp
        thirdparty/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.h
        thirdparty/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp)

add_executable(ProjectSnake ${HEADER_FILES} ${SOURCE_FILES} ${IMGUI_FILES} src/main.cpp)

if(APPLE)
    target_link_libraries(ProjectSnake "-framework OpenGL")
endif()

target_link_libraries(ProjectSnake glfw ${GLFW_LIBRARIES} libglew_static assimp)
