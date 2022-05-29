#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "App.hpp"
#include "Level.h"
#include "Reader.h"

#include "helpers/RootDir.hpp"

#include "Quadtree.h"

static App& get_app(GLFWwindow* window) {
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}

int main() {


    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Thomas Was Alone", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // Create the App
    App app;
    //app.setWindow(window);

    // Hook user inputs to the App
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(&app));

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        get_app(window).key_callback(key, scancode, action, mods);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        get_app(window).size_callback(width, height);
    });

     // Force call the size_callback of the app to set the right viewport and projection matrix
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    app.size_callback(width, height);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        app.Update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }



    glfwTerminate();
    return 0;
}
