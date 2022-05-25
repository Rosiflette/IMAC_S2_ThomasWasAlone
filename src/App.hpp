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
#include "Camera.h"



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
    void startMenu2();
    void endMenu();
    void displayLevel();

    Level currentLevel;
    Quadtree qt;
    float velocity;
    // glm::vec2 lastMove;
    int numChar; //indice du character
    int getHeight();
    int getWidth();
    glm::vec2 topLeftLvl;
    glm::vec2 bottomRightLvl;



private:
    void LoadImage(const std::string& imagePath);
    void Render();
    glm::vec2 rotateVec2(const glm::vec2& vec, const glm::vec2& center, const float& angle);
    void setCamera();

    bool checkFinalPos();

    void generateTexture();
    void generateTextureBackground();
    void textureLvl1();
    void textureLvl2();
    void checkCollison(std::vector<Rectangle> list, float mv, int direction);
    void drawArrow();
    void drawCircle(float cx, float cy, float ray, int num_segments,float r, float g, float b);
    void drawEyes();
    void drawEnd();
    void setQuadtree(glm::vec2 tL, glm::vec2 bR);
    void setCurrentPlayer();
    void movement(glm::vec2 deplacement,std::vector<Rectangle> listRInSec, float gravity);
    bool isDead();
    void readLvl();
    


    int _width;
    int _height;
    float _viewSize;
    double _previousTime;
    bool isColliding;

    GLuint _textureId;

    
    Level lvl;
    // Reader r;
    Rectangle test;
    Reader read;
    float deltaTime;
    double currentTime;
    Camera camera;
    bool isJumping;
    float speed;
    float mouvmentX;
    

    int page; // 1 = menu, 2 = jeu

};

