#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "App.hpp"
#include "Level.h"
#include "Reader.h"

#include "helpers/RootDir.hpp"

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
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGLTemplate", nullptr, nullptr);
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

    // Hook user inputs to the App
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(&app));

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        get_app(window).key_callback(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        get_app(window).mouse_button_callback(button, action, mods);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        get_app(window).scroll_callback(xoffset, yoffset);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        get_app(window).cursor_position_callback(xpos, ypos);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        get_app(window).size_callback(width, height);
    });

     // Force call the size_callback of the app to set the right viewport and projection matrix
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    std::cout << "width " << width << std::endl;
    std::cout << "height" << height << std::endl;
    app.size_callback(width, height);
    
    //Level lvl;

    Reader r(std::string(ROOT_DIR) + "src/level.txt");
    Level lvl = r.readNextLevel();

    for (size_t i = 0; i < lvl.getObstacles().size(); i++) {
      std::cout << "Rectangle " << i << std::endl;
      lvl.getObstacles()[i].displayValues();
    }
    std::cout << "Character " << std::endl;
    lvl.getCharacter().displayValues();

    app.currentLevel = lvl;

    Level lvl2 = r.readNextLevel();
    for (size_t i = 0; i < lvl2.getObstacles().size(); i++) {
      std::cout << "Rectangle " << i << std::endl;
      lvl2.getObstacles()[i].displayValues();
    }

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        app.Update();
        
        //startMenu();

        //app.displayLevel();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }



    glfwTerminate();
    return 0;
}
