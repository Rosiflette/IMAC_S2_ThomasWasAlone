
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
  this->color= glm::vec3(std::fmod(col.x,255), std::fmod(col.y,255), std::fmod(col.z,255));
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
