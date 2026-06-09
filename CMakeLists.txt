cmake_minimum_required(VERSION 3.16)

project(PhysarumSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw)

# GLAD
add_library(glad STATIC
    glad/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/glad
)

# Executável
add_executable(sim
    src/main.cpp
    src/simulation.cpp
)

# Headers do projeto
target_include_directories(sim PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/glad
)

# Bibliotecas
target_link_libraries(sim PRIVATE
    glad
    glfw
)

# Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(sim PRIVATE
        GL
        dl
        pthread
    )
endif()

# Windows
if(WIN32)
    target_link_libraries(sim PRIVATE
        opengl32
        gdi32
    )
endif()