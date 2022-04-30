#include "Character.h"

Character::Character(){}

Character::Character(glm::vec2 pos,float w,float h, glm::vec3 col, glm::vec2 positionArrivee): Rectangle(pos,w,h,col){
  this->positionArrivee = positionArrivee;
}

void Character::displayValues(){
  Rectangle::displayValues();
  std::cout << "Position arrivée x, y : " << this->positionArrivee.x << "," << this->positionArrivee.y << std::endl;
}

void Character::move(float deltaTime){
    float speed = 3.0;
    this->position.x += speed*deltaTime;
}

void Character::jump(float deltaTime){
    float gravity = 9.81;
    float power = 0.1;
    float speed = 0;
    speed += gravity*power;
    this->position.y += speed*deltaTime;

}