#include <GLFW/glfw3.h>
#include "glfw_window.h"
#include "graphics.h"
#include "glfw_initilazition.h"

#include<iostream>

std::int32_t main(std::int32_t argc, gsl::zstring* argv) {
    const veng::GlfwInitialization _glfw;

    veng::Window window("Babo engine",{800,500});


    while(!window.ShouldClose()){
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}