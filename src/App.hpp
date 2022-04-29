#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <glm/glm.hpp>

//c'est ici qu'il faut le mettre ??
#include "Display.h"
#include "Rectangle.h"
#include "Level.h"



class App {
public:
    App();
    void Update();
    
    // callbacks users input
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);
    //fonctions qu'on a ajouté
    void startMenu();
    void displayLevel();
    Level currentLevel;

private: 
    void Render();
    glm::vec2 rotateVec2(const glm::vec2& vec, const glm::vec2& center, const float& angle);

    int _width;
    int _height;
    double _previousTime;

    GLuint _textureId;

    float _imageAngle;

    int page; // 1 = menu, 2 = jeu
    
};


void drawRectangle(Rectangle rec);
