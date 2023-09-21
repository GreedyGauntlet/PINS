cmake_minimum_required(VERSION 3.0.0)
project(Test)

add_executable(Test src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw/)
add_subdirectory(vendor/imgui/)
target_link_libraries(Test glfw)
target_link_libraries(Test OpenGL::GL)
target_link_libraries(Test imgui)