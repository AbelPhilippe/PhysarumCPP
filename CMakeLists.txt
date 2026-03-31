cmake_minimum_required(VERSION 3.16)
project(PhysarumSim)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

#                   GLFW Download
# ---------------------------------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
# ---------------------------------------------------

FetchContent_MakeAvailable(glfw)

add_library(glad
    glad/glad.c
)

target_include_directories(glad PUBLIC
    glad
)

add_executable(sim
    main.cpp
)

target_include_directories(sim PRIVATE
    glad
)

target_link_libraries(sim
    glad
    glfw
)

if(UNIX AND NOT APPLE)
    target_link_libraries(sim GL dl pthread)
endif()

if(WIN32)
    target_link_libraries(sim opengl32 gdi32)
endif()