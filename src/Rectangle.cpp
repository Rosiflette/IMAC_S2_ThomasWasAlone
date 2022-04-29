
#include "Rectangle.h"

Rectangle::Rectangle(){
  this->position = glm::vec2(0, 0);
  this->w = 0;
  this->h = 0;
  this->color= glm::vec3(0, 0, 0);
}

//initialize rectangle
Rectangle::Rectangle(glm::vec2 pos,float w,float h, glm::vec3 col){
  this->position = pos;
  this->w = w;
  this->h = h;
  this->color= glm::vec3(std::fmod(col.x,256), std::fmod(col.y,256), std::fmod(col.z,256));
}

glm::vec2 Rectangle::getPosUpperLeft(){
    return this->position;
}

//Get the position of upper right corner
glm::vec2 Rectangle::getPosUpperRight(){
    glm::vec2 vect = glm::vec2((this->position.x + this->w), this->position.y);
    return vect;
}

//Get the position of bottom left corner
glm::vec2 Rectangle::getPosBottomLeft(){
    glm::vec2 vect = glm::vec2(this->position.x, (this->position.y+ this->h));
    return vect;
}

//Get the position of bottom right corner
glm::vec2 Rectangle::getPosBottomRight(){
    glm::vec2 vect = glm::vec2((this->position.x + this->w), (this->position.y+this->h));
    return vect;
}

//Get the color
glm::vec3 Rectangle::getColor(){
    return this->color;
}


void Rectangle::displayValues(){
  std::cout << "Position x, y : " << this->position.x << "," << this->position.y << std::endl;
  std::cout << "Taille width, height : " << this->w << "," << this->h << std::endl;
  std::cout << "Couleur r, g, b : " << this->color.x << "," << this->color.y << "," << this->color.z << std::endl;
}

void Rectangle::draw(){
  glBegin(GL_POLYGON);
      glColor3f(this->getColor().x,this->getColor().y,this->getColor().z );
      glVertex2f(this->getPosUpperLeft().x,this->getPosUpperLeft().y);
      glVertex2f(this->getPosBottomLeft().x,this->getPosBottomLeft().y);
      glVertex2f(this->getPosBottomRight().x,this->getPosBottomRight().y);
      glVertex2f(this->getPosUpperRight().x,this->getPosUpperRight().y);
  glEnd();
}