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

App::App(float viewSize) : _previousTime(0.0), _viewSize(viewSize){
    //Page 1 = start menu
    this->page = 1;

    //Read 1st Level
    read = Reader(std::string(ROOT_DIR) + "src/levels.txt");
    this->currentLevel = read.readNextLevel();
    this->currentLevel.setNumLevel(1);

    //Set Quadtree and set the size of the level
    topLeftLvl = currentLevel.getScreenLvl()[0];
    bottomRightLvl = currentLevel.getScreenLvl()[1];
    setQuadtree(topLeftLvl,bottomRightLvl);

    //Number of current character
    numChar = 0;

    //Camera creation
    camera = Camera();

    //Speed of the moving platform
    speed = 0.1;

   
}

//load the image and return the texture 
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

    currentTime = glfwGetTime();

    deltaTime = currentTime - _previousTime;
    _previousTime = currentTime;

    Render();
}

//main while render
void App::Render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    //Movement
    float gravity = -0.002;
    glm::vec2 deplacement = currentLevel.getCharacters()[numChar].getValMouvments(glm::vec2(0,gravity));

    //List of rectangles near the current player
    std::vector<Rectangle> listRInSec;
    listRInSec = qt.seachListRectangles(currentLevel.getCharacters()[numChar].getPosUpperLeft(), currentLevel.getCharacters()[numChar].getPosBottomRight(),currentLevel.getCharacters()[numChar].getPosBottomLeft(), currentLevel.getCharacters()[numChar].getPosUpperRight());
    for(int i =0; i<3; i++){
        if(numChar != i){
            listRInSec.push_back(currentLevel.getCharacters()[i]);
        }
    }
    //tell us if the character is in collision
    inCollision = currentLevel.getCharacters()[numChar].inCollision(listRInSec, deplacement);

    //Start Menu
    if(page == 1){
        if((int)currentTime%2){
            accueil1();
        }
        else{
            accueil2();
        }
        generateTexture();
    }

    //1st Level
    if(page == 2){
        
        
        if(checkFinalPos()){
            //Set next level
            page = 3;
            textureLvl2();
            numChar = 0;
            this->currentLevel.setNumLevel(this->currentLevel.getNumLevel()+1);
            this->currentLevel = read.readNextLevel();
            camera.followCharacter(currentLevel.getCharacters()[numChar]);
            
        }

        //Check if current player is dead
        if(isDead()){
            readLvl();
        }
        
        //Handle movement + collision
        movement(deplacement, listRInSec, gravity);
        setCamera();

        //The display
        generateTextureBackground();
        displayLevel();
        //qt.drawSection();
        drawArrow();
        drawEyes();
        
        

    }

    //2nd Level
    if(page == 3){
        currentLevel.setNumLevel(2);

        if(checkFinalPos()){
            endMenu();
            page = 4;
        }
        
        if(isDead()){
            readLvl();
        }
        
        //Handle movement + collision
        movement(deplacement, listRInSec, gravity);
        movingPlatform();
        setCamera();

        //The display
        generateTextureBackground();
        displayLevel();
        //qt.drawSection();
        setQuadtree(topLeftLvl,bottomRightLvl);
        drawArrow();
        drawEyes();
        
    }

    //end display
    if(page == 4){
        generateTextureBackground();
    }

    //rules display
    if(page==10){
        //RULES OF THE GAME
        generateRules();
    }

    
}

//move a plateform in level 2
void App::movingPlatform(){
        mouvmentX+=speed*deltaTime;
     
        if(mouvmentX<0.15){
            speed = 0.1;
            
        }
        if(mouvmentX>1){
            speed = -0.1;
        }
        
        Rectangle newObstacle = currentLevel.getObstacles()[2];
        newObstacle.movingPlatform(mouvmentX);
        currentLevel.setObstacle(newObstacle,2);
}

//create the quadtree with the size of the level
void App::setQuadtree(glm::vec2 tL, glm::vec2 bR){
        qt = Quadtree(tL,bR);
        for (int i = 0; i < (int)currentLevel.getObstacles().size(); i++) {
        qt.addRectangleIntoSection(currentLevel.getObstacles()[i], 6);
        }
}

bool App::isDead(){
    Character currentPlayer = currentLevel.getCharacters()[numChar];
    if(currentPlayer.getPosUpperLeft().x < topLeftLvl.x || currentPlayer.getPosUpperLeft().x > bottomRightLvl.x || currentPlayer.getPosUpperLeft().y < bottomRightLvl.y ){
        return true;
    }
    return false;
}

void App::readLvl(){
    read = Reader(std::string(ROOT_DIR) + "src/levels.txt");
    int num = this->currentLevel.getNumLevel();
    for(int i = 0; i< num; i++){
        this->currentLevel = read.readNextLevel();
    }
    this->currentLevel.setNumLevel(num);
    camera.followCharacter(currentLevel.getCharacters()[numChar]);
    
}

void App::setCamera(){
    //Follow the current player on horizontal axe
    if(currentLevel.getCharacters()[numChar].getPosUpperLeft().x > 0 && currentLevel.getCharacters()[numChar].getPosUpperRight().x < currentLevel.getScreenLvl()[1].x- 1.78){
        camera.followCharacter(currentLevel.getCharacters()[numChar]);
    }
    
}

    
void App::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {
    glm::vec2 acceleration = {0,0};
    float acc = 0.02; 

    
    keyState[key]=action!=GLFW_RELEASE; //create an array to save the key actions (for multiple keys actions)
   

    //menu
    if(key == GLFW_KEY_ENTER && page == 1){
        page = 2;
        textureLvl1();
    }
    //rules
    else if(key == GLFW_KEY_R && page == 1){
        page = 10;
        countRules = 0;
    }
    //back to menu
    else if(key == GLFW_KEY_B && page ==10){
        page = 1;
    }
    
    //Key for movements
    else{
        //Up + right
        if(keyState[GLFW_KEY_UP] && keyState[GLFW_KEY_RIGHT] ){
        
            if(inCollision){
                    acceleration.y += acc*currentLevel.getCharacters()[numChar].getJumpPower();
                    acceleration.x += 2*acc;
                }
        
        }
        //Up + left
        else if(keyState[GLFW_KEY_UP] && keyState[GLFW_KEY_LEFT] ){
        
            if(inCollision){
                    acceleration.y += acc*currentLevel.getCharacters()[numChar].getJumpPower();
                    acceleration.x -= 2*acc;
                }
        
        }
        else if(keyState[GLFW_KEY_RIGHT]){
            acceleration.x += 0.2*acc;
        }
        else if(keyState[GLFW_KEY_LEFT]){
            acceleration.x -= 0.2*acc;
        }
        else if(keyState[GLFW_KEY_UP]){

            if(inCollision){
                acceleration.y += acc*currentLevel.getCharacters()[numChar].getJumpPower();
            }
            
        }
        else if(keyState[GLFW_KEY_DOWN]){
          acceleration.y -= 0.2*acc;
        }

       
        //swap current player
        if(keyState[GLFW_KEY_TAB]){
            int nbChar = currentLevel.getCharacters().size();
            
            if(numChar < nbChar-1){
                numChar ++;
            }
            else{
                numChar = 0;
            }
            camera.followCharacter(currentLevel.getCharacters()[numChar]);
            
        }
            //move the player
            currentLevel.getCharacters()[numChar].mouvments(acceleration, deltaTime);
        
    }
    

}


void App::movement(glm::vec2 deplacement,std::vector<Rectangle> listRInSec, float gravity){

    int i = 0;
    isColliding = false;

      //if player go esright of left  
      if( deplacement.x > deplacement.y){
      //we check first horizontal collisions    
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
      //if the player goes up we check first vertical collisions 
      while(i < (int)listRInSec.size() && !isColliding){
        isColliding = currentLevel.getCharacters()[numChar].collision(listRInSec[i], deplacement);
        i++;
      }
      
      if(isColliding){
        deplacement.y = currentLevel.getCharacters()[numChar].collisionVertical(listRInSec[--i], deplacement);
        isColliding = false;
        if(deplacement.y == listRInSec[--i].getPosBottomLeft().y){
            currentLevel.getCharacters()[numChar].setPositionY(deplacement.y);
        }
        else{
            currentLevel.getCharacters()[numChar].mouvments((glm::vec2(0,0.0008)),deltaTime);
        }
        
      }
      else{
        currentLevel.getCharacters()[numChar].mouvments((glm::vec2(0,gravity)), deltaTime);
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

//normalize the window
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



//Start Menu
void App::accueil1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/accueil1.jpg";
    LoadImage(imagePath);

}

void App::accueil2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/accueil2.jpg";
    LoadImage(imagePath);

}
//Rules
void App::rules(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesBase.jpg";
    LoadImage(imagePath);

}

void App::rulesUp1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesUp1.jpg";
    LoadImage(imagePath);

}

void App::rulesUp2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesUp2.jpg";
    LoadImage(imagePath);

}

void App::rulesRight1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesRight1.jpg";
    LoadImage(imagePath);

}

void App::rulesRight2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesRight2.jpg";
    LoadImage(imagePath);

}

void App::rulesLeft1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesLeft1.jpg";
    LoadImage(imagePath);

}

void App::rulesLeft2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesLeft2.jpg";
    LoadImage(imagePath);

}

void App::rulesTab1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesTab1.jpg";
    LoadImage(imagePath);

}

void App::rulesTab2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesTab2.jpg";
    LoadImage(imagePath);

}

void App::rulesTab3(){
    std::string imagePath = std::string(ROOT_DIR) + "res/rulesTab3.jpg";
    LoadImage(imagePath);

}

//Texture levels
void App::textureLvl1(){
    std::string imagePath = std::string(ROOT_DIR) + "res/textureLvl1.jpg";
    LoadImage(imagePath);

}

void App::textureLvl2(){
    std::string imagePath = std::string(ROOT_DIR) + "res/textureLvl2.jpg";
    LoadImage(imagePath);

}

//End Menu
void App::endMenu(){
    std::string imagePath = std::string(ROOT_DIR) + "res/endMenu.jpg";
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

//Generate the texture following the camera
void App::generateTextureBackground(){
        glm::vec2 tl = glm::vec2(camera.getPosition().x - (float)1280/720, camera.getPosition().y + 1);
        glm::vec2 tr = glm::vec2(camera.getPosition().x + (float)1280/720 , camera.getPosition().y + 1);
        glm::vec2 bl = glm::vec2(camera.getPosition().x - (float)1280/720, camera.getPosition().y - 1);
        glm::vec2 br = glm::vec2(camera.getPosition().x + (float)1280/720, camera.getPosition().y - 1);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);

            glTexCoord2d(0,0); glVertex2f(tl.x, 1);


            glTexCoord2d(1,0); glVertex2f(tr.x, 1);


            glTexCoord2d(1,1); glVertex2f(br.x, -1);


            glTexCoord2d(0,1); glVertex2f(bl.x,-1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}

//Drawing code
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


void App::drawCircle(float cx, float cy, float ray, int num_segments, float r, float g, float b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r,g,b);
    for (int i = 0; i < num_segments; i++)   {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
        float x = ray * cosf(theta);//calculate the x component 
        float y = ray * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void App::drawEyes(){
    Character currentPlayer = currentLevel.getCharacters()[numChar];
    float cxL = currentPlayer.getPosUpperLeft().x+(1/3.0)*currentPlayer.getWidth();
    float cyL = currentPlayer.getPosUpperLeft().y-(1/3.0)*currentPlayer.getHeight();

    float cxR = currentPlayer.getPosUpperRight().x-(1/3.0)*currentPlayer.getWidth();
    float cyR = currentPlayer.getPosUpperRight().y-(1/3.0)*currentPlayer.getHeight();

    drawCircle(cxL,cyL,0.01,10,1,1,1);
    drawCircle(cxR,cyR,0.01,10,1,1,1);

    drawCircle(cxL+0.002,cyL+0.002,0.007,10,0,0,0);
    drawCircle(cxR+0.002,cyR+0.002,0.007,10,0,0,0);
}

//Rules textures
void App::generateRules(){
    if(countRules <5){
          rules();
          countRules++;  
        }
        else if(countRules >=5 && countRules <10){
           rulesUp1();
           countRules++; 
        }
        else if(countRules>=4 && countRules <15){
           rulesUp2(); 
           countRules++; 
        }
        else if(countRules>=15 && countRules <20){
           rulesUp2();
           countRules++; 
        }
        else if(countRules>=20 && countRules <25){
           rules();
           countRules++; 
        }
        else if(countRules>=25 && countRules<30){
           rulesRight1();
           countRules++; 
        }
        else if(countRules>=30 && countRules<35){
           rulesRight2();
           countRules++; 
        }
        else if(countRules>=35 && countRules<40){
           rulesLeft1();
           countRules++; 
        }
        else if(countRules>=40 && countRules<45){
           rulesLeft2();
           countRules++; 
        }
        else if(countRules>=45 && countRules<50){
           rules();
           countRules++; 
        }
        else if(countRules>=50 && countRules<55){
           rulesTab1();
           countRules++; 
        }
        else if(countRules>=55 && countRules<60){
           rulesTab2();
           countRules++; 
        }
        else if(countRules>=60 && countRules<65){
           rulesTab3();
           countRules++; 
        }
        else{
            rules();
            countRules =0;
        }
        generateTexture();
    }
