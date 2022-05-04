#include "App.hpp"
#include "Reader.h"

#include <iostream>
#include <string>

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <glm/glm.hpp>
//#include <glm/gtx/rotate_vector.hpp>

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
      qt.addRectangleIntoSection(lvl.getObstacles()[i], 1);
    }

    // EXEMPLE UTILISATION RECHERCHE DANS LE QUADTREE -> à chaque fois pour savoir avec quoi le character va collisionner. listRInSec contient les rectangles à comparer avec la pos du joueur
    // std::vector<Rectangle> listRInSec;
    // listRInSec = qt.search(glm::vec2(-1.4, -0.8));

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
    
    // update imageAngle (use elapsedTime to update without being dependent on the frame rate)
    //_imageAngle = fmod(_imageAngle + 10.0f * (float)elapsedTime, 360.0f);

    // if(page == 1){
    //     startMenu();
    // }

    Reader r(std::string(ROOT_DIR) + "src/levels.txt");
    lvl = r.readNextLevel();

    

    Render();

}

void App::Render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //lvl.getCharacter().draw(1);
    // glClearColor(0.f, 0.f, 0.f, 1.f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);


    //const float imageAngleRad = glm::radians(_imageAngle);
    //Render the texture on the screen

    if(page == 1){
       //Render the texture on the screen
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        //glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
            
            glTexCoord2d(0,0); glVertex2f(-1.7, 1);

            
            glTexCoord2d(1,0); glVertex2f(1.7, 1);

         
            glTexCoord2d(1,1); glVertex2f(1.7, -1);

           
            glTexCoord2d(0,1); glVertex2f(-1.7, -1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    if(page == 2){
        displayLevel();
        qt.drawSection();
        
        // if(!currentLevel.getCharacter().isCollision(qt.search(currentLevel.getCharacter().getPosUpperLeft()))){
        //     currentLevel.getCharacter().gravity(deltaTime);
        // }
    }

    if(velocity > 0){
        velocity -= 0.15;
    }
    if(currentLevel.getCharacter().isJumping){ //remettre à false
        currentLevel.getCharacter().jump(velocity, deltaTime);
    }
}

void App::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {

    std::vector<Rectangle> listRInSec;
    listRInSec = qt.search(currentLevel.getCharacter().getPosUpperLeft());
    velocity = 2.0;
    // std::cout << key << std::endl;
    if(key == GLFW_KEY_ENTER && page == 1 ){
        std::cout << "Enter is pressed" << std::endl;
        page = 2;
    }
    else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        if(!currentLevel.getCharacter().isCollision(listRInSec))
            currentLevel.getCharacter().move(velocity,deltaTime);
    }
    else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        if(!currentLevel.getCharacter().isCollision(listRInSec)){
            currentLevel.getCharacter().move(velocity, -deltaTime);
        }
    }
    else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        if(currentLevel.getCharacter().isJumping == false){
            //velocity = 2.0;
            currentLevel.getCharacter().isJumping = true;
        }

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

// glm::vec2 App::rotateVec2(const glm::vec2& vec, const glm::vec2& center, const float& angle) {
//     return glm::rotate(vec-center,  glm::radians(angle))+center;
// }

static App& get_app(GLFWwindow* window) {
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}


//Menu de debut
void App::startMenu(){
    std::string imagePath = std::string(ROOT_DIR) + "res/StartMenuBIG.jpg";
    LoadImage(imagePath);

}

void App::displayLevel(){

    for(int i=0; i<(int)this->currentLevel.getObstacles().size(); i++){
        this->currentLevel.getObstacles()[i].draw(1);
        //this->currentLevel.getObstacles()[i].displayValues();
    }
    this->currentLevel.getCharacter().draw(1);
    
}