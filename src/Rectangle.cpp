
#include "Rectangle.h"
#include "glad/glad.h"
#include <stdlib.h>
#include <math.h> 

//constructors
Rectangle::Rectangle(){
  this->topLeft = glm::vec2(0,0);
  this->botRight = glm::vec2(0,0);
  this->color= glm::vec3(0, 0, 0);
  this->width = abs(this->botRight.x-this->topLeft.x);
  this->height = abs(this->topLeft.y-this->botRight.y);
}

Rectangle::Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight){
  this->topLeft = positionTopLeft;
  this->botRight = positionBotRight;
  this->color = glm::vec3(1,1,1);
  this->width = abs(this->botRight.x-this->topLeft.x);
  this->height = abs(this->topLeft.y-this->botRight.y);
}

//initialize rectangle
Rectangle::Rectangle(glm::vec2 positionTopLeft,glm::vec2 positionBotRight, glm::vec3 col){
  this->topLeft = positionTopLeft;
  this->botRight = positionBotRight;
  this->color = glm::vec3(std::fmod(col.x,256)/255, std::fmod(col.y,256)/255, std::fmod(col.z,256)/255);
  this->width = abs(this->botRight.x-this->topLeft.x);
  this->height = abs(this->topLeft.y-this->botRight.y);
}

//Get the position of upper left corner
glm::vec2 Rectangle::getPosUpperLeft(){
    return this->topLeft;
}

//Get the position of bottom left corner
glm::vec2 Rectangle::getPosBottomLeft(){
    glm::vec2 vect = glm::vec2(this->topLeft.x, this->topLeft.y - this->height);
    return vect;
}

//Get the position of bottom right corner
glm::vec2 Rectangle::getPosBottomRight(){
    glm::vec2 vect = glm::vec2((this->topLeft.x + this->width), this->topLeft.y - this->height);
    return vect;
}

//Get the position of upper right corner
glm::vec2 Rectangle::getPosUpperRight(){
    glm::vec2 vect = glm::vec2((this->topLeft.x + this->width), this->topLeft.y);
    return vect;
}

//Getters
glm::vec3 Rectangle::getColor(){
    return this->color;
}

float Rectangle::getWidth(){
    return this->width;
}

float Rectangle::getHeight(){
    return this->height;
}

//Display the attributs of the rectangle
void Rectangle::displayValues(){
  std::cout << "PositionTopLeft x, y : " << this->getPosUpperLeft().x << "," << this->getPosUpperLeft().y << std::endl;
  std::cout << "PositionBotRight x, y : " << this->getPosBottomRight().x << "," << this->getPosBottomRight().y << std::endl;
  std::cout << "Taille width, height : " << this->getWidth() << "," << this->getHeight() << std::endl;
  std::cout << "Couleur r, g, b : " << this->color.x << "," << this->color.y << "," << this->color.z << std::endl;
}

//Return 1 if one angle of the rectangle is in the other rectangle
bool Rectangle::isRectangleInRectangle(Rectangle r){

    return (this->isPointInRectangle(r.getPosUpperLeft()) ||
        this->isPointInRectangle(r.getPosUpperRight()) ||
        this->isPointInRectangle(r.getPosBottomLeft()) ||
        this->isPointInRectangle(r.getPosBottomRight()));
}

bool Rectangle::isPointInRectangle(glm::vec2 p){
    return (p.x >= this->topLeft.x &&
        p.x <= this->botRight.x &&
        p.y <= this->topLeft.y &&
        p.y >= this->botRight.y); 
}

//display a rectangle
void Rectangle::draw(int isFilled){
  if(isFilled){
    glBegin(GL_POLYGON);
  }
  else{
    glBegin(GL_LINE_STRIP);
  }
      glColor3f(this->getColor().x,this->getColor().y,this->getColor().z );
      glVertex2f(this->getPosUpperLeft().x,this->getPosUpperLeft().y);
      glVertex2f(this->getPosBottomLeft().x,this->getPosBottomLeft().y);
      glVertex2f(this->getPosBottomRight().x,this->getPosBottomRight().y);
      glVertex2f(this->getPosUpperRight().x,this->getPosUpperRight().y);
  glEnd();
}

//moving platform
void Rectangle::movingPlatform(float posX){
  this->topLeft.x = posX;
}


