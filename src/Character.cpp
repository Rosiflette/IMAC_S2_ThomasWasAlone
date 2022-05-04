#include "Character.h"

Character::Character(){}

Character::Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee): Rectangle(posTL,posBR,col){
  this->positionArrivee = positionArrivee;
  this->isJumping = false;
}

void Character::displayValues(){
  Rectangle::displayValues();
  std::cout << "Position arrivée x, y : " << this->positionArrivee.x << "," << this->positionArrivee.y << std::endl;
}

void Character::move(float velocity, float deltaTime){
    if(velocity < 0){
      isMoving= false;
    }
    else{
      this->topLeft.x += velocity*deltaTime;
    }
    
}

void Character::jump(float velocity, float deltaTime){

  if(velocity < 0){
    isJumping = false;
  }
  else{
    this->topLeft.y = this->topLeft.y + velocity*deltaTime;
  }
    
    // float gravity = 9.81;
    // float power = 0.2;
  
    // speed += gravity*deltaTime;
    // if(this->topLeft.y < + power){
    //   this->topLeft.y += speed*deltaTime;
    // }
    // else{
    //   isJumping = false;
    // }

}

void Character::gravity(float deltaTime){
    this->topLeft.y -= 0.7*deltaTime;
}

bool Character::collision(Rectangle r){

    if((this->getPosBottomRight().x > r.getPosUpperLeft().x)
    && (this->getPosUpperLeft().x < r.getPosBottomRight().x)
    && (this->getPosBottomRight().y < r.getPosUpperLeft().y) 
    && (this->getPosUpperLeft().y > r.getPosBottomRight().y))
    {
        return true;
    }
    else{
        
        return false;
    }
}

bool Character::isCollision(std::vector<Rectangle> list){
  for(int i = 0; i<list.size(); i++){
    if(collision(list[i])){
      return true;
    }
  }
}