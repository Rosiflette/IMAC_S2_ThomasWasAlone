
#include "Rectangle.h"
#include "glad/glad.h"
#include <stdlib.h>

Rectangle::Rectangle(){
  this->topLeft = glm::vec2(0,0);
  this->botRight = glm::vec2(0,0);
  this->color= glm::vec3(0, 0, 0);
}

Rectangle::Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight){
  this->topLeft = positionTopLeft;
  this->botRight = positionBotRight;
  this->color = glm::vec3(1,1,1);
}

//initialize rectangle
Rectangle::Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight, glm::vec3 col){
  this->topLeft = positionTopLeft;
  this->botRight = positionBotRight;
  this->color = glm::vec3(std::fmod(col.x,256)/255, std::fmod(col.y,256)/255, std::fmod(col.z,256)/255);
}

float Rectangle::getWidth(){
    return abs(this->botRight.x-this->topLeft.x);
}

float Rectangle::getHeight(){
    return abs(this->topLeft.y-this->botRight.y);
}
//Get the position of upper left corner
glm::vec2 Rectangle::getPosUpperLeft(){
    return this->topLeft;
}

//Get the position of upper right corner
glm::vec2 Rectangle::getPosUpperRight(){
    glm::vec2 vect = glm::vec2((this->topLeft.x + this->getWidth()), this->topLeft.y);
    return vect;
}

//Get the position of bottom left corner
glm::vec2 Rectangle::getPosBottomLeft(){
    glm::vec2 vect = glm::vec2(this->botRight.x - this->getWidth(), this->botRight.y);
    return vect;
}

//Get the position of bottom right corner
glm::vec2 Rectangle::getPosBottomRight(){
    return this->botRight;
}

//Get the color
glm::vec3 Rectangle::getColor(){
    return this->color;
}


void Rectangle::displayValues(){
  std::cout << "PositionTopLeft x, y : " << this->getPosUpperLeft().x << "," << this->getPosUpperLeft().y << std::endl;
  std::cout << "PositionBotRight x, y : " << this->getPosBottomRight().x << "," << this->getPosBottomRight().y << std::endl;
  std::cout << "Taille width, height : " << this->getWidth() << "," << this->getHeight() << std::endl;
  std::cout << "Couleur r, g, b : " << this->color.x << "," << this->color.y << "," << this->color.z << std::endl;
}

// avec des recangles droits (pas penchés)
// return 1 si l'un des 4 angles du rectangle r est dans le rectangle this
bool Rectangle::isRectangleInRectangle(Rectangle r){

  // std::cout << "jksbdkqj" << std::endl;
  // if(this->isPointInRectangle(r.getPosUpperLeft())){
  //   std::cout << "a" << std::endl;
  // }
  // if(this->isPointInRectangle(r.getPosUpperRight())){
  //   std::cout << "b" << std::endl;
  // }
  //   if(this->isPointInRectangle(r.getPosBottomLeft())){
  //   std::cout << "c" << std::endl;
  // }
  //   if(this->isPointInRectangle(r.getPosBottomRight())){
  //   std::cout << "d" << std::endl;
  // }

    return (this->isPointInRectangle(r.getPosUpperLeft()) ||
        this->isPointInRectangle(r.getPosUpperRight()) ||
        this->isPointInRectangle(r.getPosBottomLeft()) ||
        this->isPointInRectangle(r.getPosBottomRight()));
}

bool Rectangle::isPointInRectangle(glm::vec2 p){
    // std::cout << "ahhhhhhhhhhh" << std::endl;
    // if(p.x >= this->topLeft.x){
    //   std::cout << "ah" << std::endl;
    // }
    // if(p.x <= this->botRight.x){
    //   std::cout << "bh" << std::endl;
    // }
    //   if(p.y <= this->topLeft.y){
    //   std::cout << "ch" << std::endl;
    // }
    //   if(p.y >= this->botRight.y){
    //   std::cout << "dh" << std::endl;
    // }
    return (p.x >= this->topLeft.x &&
        p.x <= this->botRight.x &&
        p.y <= this->topLeft.y &&
        p.y >= this->botRight.y); // A VERIFIER SELON L'AXE
}


void Rectangle::draw(){
  glBegin(GL_LINE_STRIP);
      glColor3f(this->getColor().x,this->getColor().y,this->getColor().z );
      glVertex2f(this->getPosUpperLeft().x,this->getPosUpperLeft().y);
      glVertex2f(this->getPosBottomLeft().x,this->getPosBottomLeft().y);
      glVertex2f(this->getPosBottomRight().x,this->getPosBottomRight().y);
      glVertex2f(this->getPosUpperRight().x,this->getPosUpperRight().y);
  glEnd();
}