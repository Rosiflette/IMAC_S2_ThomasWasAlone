#include "App.hpp"
#include "Reader.h"

#include <iostream>
#include <string>

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <glm/glm.hpp>


#include "helpers/RootDir.hpp"


App::App(): App(2.0f){
    
}

App::App(float viewSize) : _previousTime(0.0), _imageAngle(0.0f), _viewSize(viewSize){

    this->page = 1;
    startMenu();

    // EXEMPLE UTILISATION READER -> lire un niveau
    Reader r(std::string(ROOT_DIR) + "src/levels.txt");
    Level lvl = r.readNextLevel();
    this->currentLevel = lvl;

    // EXEMPLE UTILISATION QUADTREE -> créer le quadtree une fois après avoir chargé le niveaux en court
    qt = Quadtree(glm::vec2((float)-1280/720, 1.0),glm::vec2((float)1280/720, -1.0));
    for (int i = 0; i < (int)lvl.getObstacles().size(); i++) {
      qt.addRectangleIntoSection(lvl.getObstacles()[i], 3);
    }

}

void App::LoadImage(const std::string& imagePath) {
    // Generate texture
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void App::Update() {

    double currentTime = glfwGetTime();

    deltaTime = currentTime - _previousTime;
    _previousTime = currentTime;



    Render();
}

void App::Render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    if(page == 1){
        generateTexture();
    }
    if(page == 2){
        generateTexture();
        displayLevel();
        qt.drawSection();

        glm::vec2 mv = {0,currentLevel.getCharacter().gravity(deltaTime)};
        int direction = 1;
        std::vector<Rectangle> listRInSec, listRInSecBotRight;
        listRInSec = qt.search(currentLevel.getCharacter().getPosUpperLeft());
        listRInSecBotRight = qt.search(currentLevel.getCharacter().getPosBottomRight());
        listRInSec.insert(listRInSec.end(), listRInSecBotRight.begin(), listRInSecBotRight.end());

        if(velocity > 0){
            velocity -= 0.15;
        }
        if(currentLevel.getCharacter().isJumping){
            direction = 0;
            mv.y = currentLevel.getCharacter().jump(velocity, deltaTime);
        }

        if(!currentLevel.getCharacter().isCollision(listRInSec, mv)){
            currentLevel.getCharacter().setPositionY(currentLevel.getCharacter().getPosUpperLeft().y + mv.y);
        }
        else {

            currentLevel.getCharacter().isJumping = false;
            for (int i = 0; i < listRInSec.size(); i++){
                currentLevel.getCharacter().setPositionIfCollision(listRInSec[i], mv.y, direction);
            }
        }
      
    }
}

void App::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {
    velocity = 2.0;
    if (action == GLFW_RELEASE)
        return;

    if(key == GLFW_KEY_ENTER && page == 1){
        page = 2;
        textureLvl();
    }
    else{
        std::vector<Rectangle> listRInSec, listRInSecBotRight;
        listRInSec = qt.search(currentLevel.getCharacter().getPosUpperLeft());
        listRInSecBotRight = qt.search(currentLevel.getCharacter().getPosBottomRight());
        listRInSec.insert(listRInSec.end(), listRInSecBotRight.begin(), listRInSecBotRight.end());

        float mv = 0.0;
        int direction = -1;

        std::cout << key << std::endl;

        if(key == GLFW_KEY_RIGHT){
            mv = currentLevel.getCharacter().calcMove(velocity,deltaTime);
            direction = 2;
        }
        if(key == GLFW_KEY_LEFT){
            mv = currentLevel.getCharacter().calcMove(velocity,-deltaTime);
            direction = 3;
        }
        if(key == GLFW_KEY_UP){
            if(currentLevel.getCharacter().isJumping == false){
                velocity = 2.0;
                currentLevel.getCharacter().isJumping = true;
            }
        }

        checkCollison(listRInSec, mv, direction);


    }
    
}


void App::checkCollison(std::vector<Rectangle> list, float mv, int direction){
    int col = 0;
    for(int i = 0; i<(int)list.size(); i++){
        col |= currentLevel.getCharacter().setPositionIfCollision(list[i], mv, direction);
    }
    if(col == 0){
        currentLevel.getCharacter().setPositionX(currentLevel.getCharacter().getPosUpperLeft().x+mv);
    }
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/) {
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/) {
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/) {
}

void App::size_callback(int width, int height) {
    _width  = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio = _width / (float) _height;

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}

static App& get_app(GLFWwindow* window) {
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}


//Menu de debut
void App::startMenu(){
    std::string imagePath = std::string(ROOT_DIR) + "res/StartMenuBIG.jpg";
    LoadImage(imagePath);

}

void App::textureLvl(){
    std::string imagePath = std::string(ROOT_DIR) + "res/sunsetPixel.jpg";
    LoadImage(imagePath);

}

void App::displayLevel(){
    for(int i=0; i<(int)this->currentLevel.getObstacles().size(); i++){
        this->currentLevel.getObstacles()[i].draw(1);
    }
    this->currentLevel.getCharacter().draw(1);
}


void App::generateTexture(){
    //Render the texture on the screen
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        //glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
            
            glTexCoord2d(0,0); glVertex2f(-1.78, 1 );

            
            glTexCoord2d(1,0); glVertex2f(1.78, 1);

         
            glTexCoord2d(1,1); glVertex2f(1.78, -1);

           
            glTexCoord2d(0,1); glVertex2f(-1.78, -1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}

// if(key == GLFW_KEY_DOWN){
//     int col = 0;
//     float mv = currentLevel.getCharacter().calcMove(velocity,-deltaTime);

//     for(int i = 0; i<(int)listRInSec.size(); i++){

//         col |= currentLevel.getCharacter().setPositionIfCollision(listRInSec[i], mv, 1);

//     }
    
//     if(col == 0){
//         currentLevel.getCharacter().setPositionY(currentLevel.getCharacter().getPosUpperLeft().y+mv);
//     }

// }