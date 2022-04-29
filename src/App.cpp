#include "App.hpp"

#include <iostream>
#include <string>

#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "helpers/RootDir.hpp"

std::string path;


App::App() : _previousTime(0.0), _imageAngle(0.0f) {

    this->page = 1;

}

void App::Update() {

    // double currentTime = glfwGetTime();
    // double elapsedTime = currentTime - _previousTime;
    // _previousTime = currentTime;
    
    // update imageAngle (use elapsedTime to update without being dependent on the frame rate)
    //_imageAngle = fmod(_imageAngle + 10.0f * (float)elapsedTime, 360.0f);

    if(page == 1){
        startMenu();
    }
    else if(page == 2){
        displayLevel();
    }

    //Render();
}

void App::Render() {
    // glClearColor(0.f, 0.f, 0.f, 1.f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // // Set up orphographic projection
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0, _width, _height, 0, -1, 1);
    // glMatrixMode(GL_MODELVIEW);

    // const glm::vec2 halfSize(_width/2.f, _height/2.f);

    // // Render the texture on the screen
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, _textureId);
    // glBegin(GL_QUADS);
    //     glm::vec2 upperLeft = rotateVec2(glm::vec2(0, 0), halfSize, _imageAngle);
    //     glTexCoord2d(0,0); glVertex2f(upperLeft.x, upperLeft.y);

    //     glm::vec2 upperRight = rotateVec2(glm::vec2(_width, 0), halfSize, _imageAngle);
    //     glTexCoord2d(1,0); glVertex2f(upperRight.x, upperRight.y);

    //     glm::vec2 bottomRight = rotateVec2(glm::vec2(_width, _height), halfSize, _imageAngle);
    //     glTexCoord2d(1,1); glVertex2f(bottomRight.x, bottomRight.y);

    //     glm::vec2 bottomLeft = rotateVec2(glm::vec2(0, _height), halfSize, _imageAngle);
    //     glTexCoord2d(0,1); glVertex2f(bottomLeft.x, bottomLeft.y);
    // glEnd();
    // glDisable(GL_TEXTURE_2D);

}

void App::key_callback(int key, int /*scancode*/, int /*action*/, int /*mods*/) {
    std::cout << key << std::endl;
    if(key == GLFW_KEY_ENTER && page == 1){
        std::cout << "Enter is pressed" << std::endl;
        page = 2;
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
}

glm::vec2 App::rotateVec2(const glm::vec2& vec, const glm::vec2& center, const float& angle) {
    return glm::rotate(vec-center,  glm::radians(angle))+center;
}

//A mettre dans display
void drawRectangle(Rectangle rec){
    glBegin(GL_POLYGON);
        glColor3f(rec.getColor().x,rec.getColor().y,rec.getColor().z );
        glVertex2f(rec.getPosUpperLeft().x,rec.getPosUpperLeft().y);
        glVertex2f(rec.getPosBottomLeft().x,rec.getPosBottomLeft().y);
        glVertex2f(rec.getPosBottomRight().x,rec.getPosBottomRight().y);
        glVertex2f(rec.getPosUpperRight().x,rec.getPosUpperRight().y);
    glEnd();
}


static App& get_app(GLFWwindow* window) {
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}


//Menu de debut
void App::startMenu(){
    //load texture
    // path = "res/StartMenuBIG.jpg";
    // App app;
    // app.Update();

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
    // tips found here for absolut ressources path: https://shot511.github.io/2018-05-29-how-to-setup-opengl-project-with-cmake/
    std::string imagePath = std::string(ROOT_DIR) + "res/StartMenuBIG.jpg";
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture of start menu" << std::endl;
    }
    stbi_image_free(data);



    //RENDER 
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Set up orphographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _width, _height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    const glm::vec2 halfSize(_width/2.f, _height/2.f);

    // Render the texture on the screen
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glBegin(GL_QUADS);
        glm::vec2 upperLeft = rotateVec2(glm::vec2(0, 0), halfSize, _imageAngle);
        glTexCoord2d(0,0); glVertex2f(upperLeft.x, upperLeft.y);

        glm::vec2 upperRight = rotateVec2(glm::vec2(_width, 0), halfSize, _imageAngle);
        glTexCoord2d(1,0); glVertex2f(upperRight.x, upperRight.y);

        glm::vec2 bottomRight = rotateVec2(glm::vec2(_width, _height), halfSize, _imageAngle);
        glTexCoord2d(1,1); glVertex2f(bottomRight.x, bottomRight.y);

        glm::vec2 bottomLeft = rotateVec2(glm::vec2(0, _height), halfSize, _imageAngle);
        glTexCoord2d(0,1); glVertex2f(bottomLeft.x, bottomLeft.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);


}

void App::displayLevel(){

    for(int i=0; i<this->currentLevel.getObstacles().size(); i++){
        drawRectangle(this->currentLevel.getObstacles()[i]);
        //this->currentLevel.getObstacles()[i].displayValues();
    }

}