#pragma once
//#define GLFW_INCLUDE_NONE
// #include "GLFW/glfw3.h"
// #include "glad/glad.h"
// #include <glm/glm.hpp>

#include <string>

#include "glad/glad.h"
#include <glm/glm.hpp>

//c'est ici qu'il faut le mettre ??
#include "Display.h"
#include "Rectangle.h"
#include "Level.h"
//A RETIRER
#include "Quadtree.h"
#include "Reader.h"



class App {
public:
    App();
    App(float viewSize);
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
    void Camera();
    Level currentLevel;
    Quadtree qt;
    float velocity;


private: 
    void LoadImage(const std::string& imagePath);
    void Render();
    glm::vec2 rotateVec2(const glm::vec2& vec, const glm::vec2& center, const float& angle);

    void generateTexture();
    void textureLvl();
    void checkCollison(std::vector<Rectangle> list, float mv, int direction);

    int _width;
    int _height;
    float _viewSize;
    double _previousTime;

    GLuint _textureId;

    float _imageAngle;
    Level lvl;
    Rectangle test;
    float deltaTime;


    int page; // 1 = menu, 2 = jeu
    
};


void drawRectangle(Rectangle rec);
