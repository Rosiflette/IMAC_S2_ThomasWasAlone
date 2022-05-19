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
    topLeftLvl = glm::vec2((float)-1280/720, 1.0);
    bottomRightLvl = currentLevel.getPosBottomRightLvl();
    qt = Quadtree(topLeftLvl,bottomRightLvl );
    for (int i = 0; i < (int)lvl.getObstacles().size(); i++) {
      qt.addRectangleIntoSection(lvl.getObstacles()[i], 6);
    }

    //Initialiser le joueur
    numChar = 0;

    //Création de la caméra
    camera = Camera();


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
      if(checkFinalPos()){
          page = 3;
      }
      if(isDead()){
          readLvl();
      }

      float gravity = -0.001; //-0.001
      // lastMove = currentLevel.getCharacters()[numChar].getPosUpperLeft();
      glm::vec2 deplacement = currentLevel.getCharacters()[numChar].getValMouvments(glm::vec2(0,gravity));

      std::vector<Rectangle> listRInSec;

      listRInSec = qt.seachListRectangles(currentLevel.getCharacters()[numChar].getPosUpperLeft(), currentLevel.getCharacters()[numChar].getPosBottomRight(),currentLevel.getCharacters()[numChar].getPosBottomLeft(), currentLevel.getCharacters()[numChar].getPosUpperRight());

      int i = 0;
      bool isColliding = false;

      if( deplacement.x > deplacement.y){
      while(i < (int)listRInSec.size() && !isColliding){
        isColliding = currentLevel.getCharacters()[numChar].collision(listRInSec[i], deplacement);
        i++;
      }

      if(isColliding){
        deplacement.x = currentLevel.getCharacters()[numChar].collisionHorizontal(listRInSec[--i], deplacement);
        currentLevel.getCharacters()[numChar].setPositionX(deplacement.x);
        isColliding = false;

      }
      i=0;
    }
      while(i < (int)listRInSec.size() && !isColliding){
        isColliding = currentLevel.getCharacters()[numChar].collision(listRInSec[i], deplacement);
        i++;
      }
      if(isColliding){
        deplacement.y = currentLevel.getCharacters()[numChar].collisionVertical(listRInSec[--i], deplacement);
        isColliding = false;
        currentLevel.getCharacters()[numChar].setPositionY(deplacement.y);
        currentLevel.getCharacters()[numChar].mouvments((glm::vec2(0,gravity)));
      }
      else{
        currentLevel.getCharacters()[numChar].mouvments((glm::vec2(0,gravity)));
      }
      i = 0;

      if( deplacement.x <= deplacement.y){
      while(i < (int)listRInSec.size() && !isColliding){
        isColliding = currentLevel.getCharacters()[numChar].collision(listRInSec[i], deplacement);
        i++;
      }

      if(isColliding){
        deplacement.x = currentLevel.getCharacters()[numChar].collisionHorizontal(listRInSec[--i], deplacement);
        currentLevel.getCharacters()[numChar].setPositionX(deplacement.x);
        isColliding = false;
      }
      i=0;
    }

      generateTextureBackground();
      displayLevel();
      qt.drawSection();
      drawArrow();
      //camera.followCharacter(currentLevel.getCharacters()[numChar]);
      setCamera();

    }
}


bool App::isDead(){
    Character currentPlayer = currentLevel.getCharacters()[numChar];
    if(currentPlayer.getPosUpperLeft().x < topLeftLvl.x || currentPlayer.getPosUpperLeft().x > bottomRightLvl.x || currentPlayer.getPosUpperLeft().y > topLeftLvl.y || currentPlayer.getPosUpperLeft().y < bottomRightLvl.y ){
        return true;
    }
    return false;
}

void App::readLvl(){
    Reader r(std::string(ROOT_DIR) + "src/levels.txt");
    lvl = r.readNextLevel();
    this->currentLevel = lvl;
    camera.followCharacter(currentLevel.getCharacters()[numChar]);
}

void App::setCamera(){
    //follow on horizontal axe
    if(currentLevel.getCharacters()[numChar].getPosUpperLeft().x > 0 && currentLevel.getCharacters()[numChar].getPosUpperRight().x < currentLevel.getPosBottomRightLvl().x - 1.78){
        camera.followCharacter(currentLevel.getCharacters()[numChar]);
    }
}

    
void App::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {

    glm::vec2 acceleration = {0,0};
    float acc = 0.02; //0.05

    if (action == GLFW_RELEASE)
        return;

    if(key == GLFW_KEY_ENTER && page == 1){
        page = 2;
        textureLvl();
    }
    else{

        if(key == GLFW_KEY_RIGHT){
          acceleration.x += acc;
        }
        if(key == GLFW_KEY_LEFT){
          acceleration.x -= acc;
        }
        if(key == GLFW_KEY_UP){
          acceleration.y += acc*3;
        }
        if(key == GLFW_KEY_DOWN){
          acceleration.y -= acc;
        }
        //swap current player
        if(key == GLFW_KEY_TAB){
            int nbChar = currentLevel.getCharacters().size();

            if(numChar < nbChar-1){
                numChar ++;
            }
            else{
                numChar = 0;
            }
        }
        currentLevel.getCharacters()[numChar].mouvments(acceleration);
    }

}


bool App::checkFinalPos(){
    //check if all characters are on their final position
    for(int c=0; c < (int)currentLevel.getCharacters().size(); c++){
        if(!currentLevel.getCharacters()[c].isInFinalPos()){
            return false;
        }
    }
    return true;
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

int App::getHeight(){
    return _height;
}

int App::getWidth(){
    return _width;
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
    //draw map
    for(int i=0; i<(int)this->currentLevel.getObstacles().size(); i++){
        this->currentLevel.getObstacles()[i].draw(1);
    }
    for(int i=0; i<(int)this->currentLevel.getCharacters().size(); i++){
        //draw character
        this->currentLevel.getCharacters()[i].draw(1);
        //draw final position
        this->currentLevel.getCharacters()[i].drawFinalPos();


    }
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


void App::generateTextureBackground(){
    //Render the texture on the screen
        glm::vec2 tl = glm::vec2(camera.getPosition().x - (float)1280/720, camera.getPosition().y + 1);
        glm::vec2 tr = glm::vec2(camera.getPosition().x + (float)1280/720 , camera.getPosition().y + 1);
        glm::vec2 bl = glm::vec2(camera.getPosition().x - (float)1280/720, camera.getPosition().y - 1);
        glm::vec2 br = glm::vec2(camera.getPosition().x + (float)1280/720, camera.getPosition().y - 1);




        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        //glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);

            glTexCoord2d(0,0); glVertex2f(tl.x, 1);


            glTexCoord2d(1,0); glVertex2f(tr.x, 1);


            glTexCoord2d(1,1); glVertex2f(br.x, -1);


            glTexCoord2d(0,1); glVertex2f(bl.x,-1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}


void App::drawArrow(){
    Character currentPlayer = currentLevel.getCharacters()[numChar];
    float characMiddle = currentPlayer.getPosUpperLeft().x+currentPlayer.getWidth()/2;
    glBegin(GL_TRIANGLES);
      glColor3f(1,1,1);
      glVertex2f(characMiddle, currentPlayer.getPosUpperLeft().y + 0.02);
      glVertex2f(characMiddle - 0.02,currentPlayer.getPosUpperLeft().y + 0.05);
      glVertex2f(characMiddle + 0.02, currentPlayer.getPosUpperLeft().y + 0.05);
    glEnd();
}
