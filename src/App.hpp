#pragma once
//#define GLFW_INCLUDE_NONE
// #include "GLFW/glfw3.h"
// #include "glad/glad.h"
// #include <glm/glm.hpp>

#include <string>

#include "glad/glad.h"
#include <glm/glm.hpp>

#include "Rectangle.h"
#include "Level.h"
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
    void size_callback(int width, int height);
    
    //window getter
    int getHeight();
    int getWidth();

    //position of level corners
    glm::vec2 topLeftLvl;
    glm::vec2 bottomRightLvl;
   
    



private:
    
    void Render();
    

    //TEXTURES
    void LoadImage(const std::string& imagePath);
    void generateTexture();
    void generateTextureBackground();
    void accueil1();
    void accueil2();
    void rules();
    void rulesUp1();
    void rulesUp2();
    void rulesRight1();
    void rulesRight2();
    void rulesLeft1();
    void rulesLeft2();
    void rulesTab1();
    void rulesTab2();
    void rulesTab3();
    void endMenu();
    void textureLvl1();
    void textureLvl2();
    
    //DISPLAY
    void displayLevel();
    void drawArrow();
    void drawEyes();
    void drawEnd();
    void generateRules();
    void drawCircle(float cx, float cy, float ray, int num_segments,float r, float g, float b);
    
    
    //MOVEMENT AND COLLISIONS
    void checkCollison(std::vector<Rectangle> list, float mv, int direction);
    void setQuadtree(glm::vec2 tL, glm::vec2 bR);
    void movement(glm::vec2 deplacement,std::vector<Rectangle> listRInSec, float gravity);
   
    
    //LEVEL LOGISTIC
    bool isDead();
    bool checkFinalPos();
    void readLvl();
    void movingPlatform();

     //CAMERA
    void setCamera();
    
 
    //window parameters
    int _width;
    int _height;
    float _viewSize;
    
    int countRules; 
    bool keyState[266];

    bool isColliding;
    bool inCollision;

    GLuint _textureId;

    float deltaTime;
    double currentTime;
    double _previousTime;
    
    int page; // 1 = menu, 2 = jeu
    Level lvl;
    Reader read;
    Camera camera;  
    Level currentLevel;
    Quadtree qt;

    int numChar; //index of current character

    //moving plateform
    float speed;
    float mouvmentX;
    

   
    
    
};

