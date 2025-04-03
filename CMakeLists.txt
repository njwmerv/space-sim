cmake_minimum_required(VERSION 3.30)
project(space_sim)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
fetchcontent_declare(GLFW GIT_REPOSITORY https://github.com/glfw/glfw.git)
fetchcontent_makeavailable(GLFW)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(space_sim main.cpp glad.c system.cc body.cc vector.cc shader.cc surface.cc render2d.cc)

target_link_libraries(space_sim glfw)