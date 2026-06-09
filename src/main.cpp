#include "glad.h"
#include <GLFW/glfw3.h>

#include "config.h"
#include "simulation.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(NULL));

    if (!glfwInit())
    {
        std::cout << "Erro GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Physarum CPP",
        NULL,
        NULL
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Erro GLAD\n";
        glfwTerminate();
        return -1;
    }

    PhysarumSim sim;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        sim.update();
        sim.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}