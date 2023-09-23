cmake_minimum_required(VERSION 3.0.0)
project(PINS)

add_executable(PINS src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw/)
add_subdirectory(vendor/imgui/)
target_link_libraries(PINS glfw)
target_link_libraries(PINS OpenGL::GL)
target_link_libraries(PINS imgui)

target_sources(PINS PRIVATE 
    src/Core/Window.cpp
    src/Core/Application.cpp
    src/Panels/CommandPanel.cpp
    src/Panels/ClientHierarchyPanel.cpp
    src/Panels/ClientDetailsPanel.cpp
)

target_include_directories(PINS PRIVATE ${CMAKE_SOURCE_DIR})