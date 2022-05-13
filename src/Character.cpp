#include "Character.h"
#include "glad/glad.h"
#include <stdlib.h>

Character::Character(){}

Character::Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee): Rectangle(posTL,posBR,col){
  this->positionArrivee = positionArrivee;
  this->speed = 1.0;
  this->isJumping = false;
}

glm::vec2 Character::getPosFinal(){
  return this->positionArrivee;
}

void Character::drawFinalPos(){
  glBegin(GL_LINE_LOOP);
      glColor3f(0.2,0.2,0.2);
      glVertex2f(this->getPosFinal().x,this->getPosFinal().y); //en bas a droite
      glVertex2f(this->getPosFinal().x,this->getPosFinal().y + this->getHeight());
      glVertex2f(this->getPosFinal().x-this->getWidth(),this->getPosFinal().y + this->getHeight());
      glVertex2f(this->getPosFinal().x-this->getWidth(),this->getPosFinal().y);
  glEnd();
}

bool Character::isInFinalPos(){
  if(abs(this->getPosFinal().x - this->getPosBottomRight().x) < 0.01 && abs(this->getPosFinal().y - this->getPosBottomRight().y) < 0.01 ){
    return true;
  }
  return false;
}

void Character::displayValues(){
  Rectangle::displayValues();
  std::cout << "Position arrivée x, y : " << this->positionArrivee.x << "," << this->positionArrivee.y << std::endl;
}

float Character::calcMove(float velocity, float deltaTime){
  return velocity*deltaTime;  
}

// float Character::moveCalcul(float velocity, float deltaTime){
//       return this->topLeft.x += this->speed*deltaTime;
// }

void Character::moveDown(float velocity, float deltaTime){
    if(velocity < 0){
      isMoving= false;
    }
    else{
      this->topLeft.y -= velocity*deltaTime;
    }
}



float Character::jump(float velocity, float deltaTime){

  if(velocity < 0){
    isJumping = false;
  }
  if(isJumping != false){
    glm::vec2 positionRel = glm::vec2(0,0);
    float g = 9.81;
    float pi = 3.14;
    int angleInit = pi/3;
    int t=0;
    double v_x = cos(angleInit)*velocity;
    double v_y = sin(angleInit)*velocity;
    positionRel.x=(int)(v_x*t);
    positionRel.y=(int)((v_y*t)-((g*t*t)/2000));
    this->topLeft += positionRel;
    return velocity*deltaTime;
  }
  return 0;
    
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

float Character::gravity(float deltaTime){
  return -0.7*deltaTime;
  
}

bool Character::collision(Rectangle r, glm::vec2 dir){

    if(((this->getPosBottomRight().x+dir.x) > r.getPosUpperLeft().x)
    && ((this->getPosUpperLeft().x+dir.x) < r.getPosBottomRight().x)
    && ((this->getPosBottomRight().y+dir.y) < r.getPosUpperLeft().y) 
    && ((this->getPosUpperLeft().y+dir.y) > r.getPosBottomRight().y))
    {
        return true;
    }
    else{
        
        return false;
    }
}

char Character::whereIsCollision(Rectangle r, float mv){
  //en haut
  if(this->getPosUpperLeft().y+mv > r.getPosBottomRight().y && this->getPosBottomRight().y+mv < r.getPosBottomRight().y){
    // std::cout<< "u" << std::endl;
    return 'u';
  }
  //Collision est en bas
  if(this->getPosBottomRight().y+mv < r.getPosUpperLeft().y && this->getPosUpperLeft().y+mv > r.getPosUpperLeft().y){
    // std::cout<< "d" << std::endl;
    return 'd';
  }
  //a droite
  if(this->getPosBottomRight().x+mv > r.getPosUpperLeft().x && this->getPosUpperLeft().x+mv < r.getPosUpperLeft().x){
    // std::cout<< "r" << std::endl;
    return 'r';
  }
  //a gauche
  if(this->getPosUpperLeft().x+mv < r.getPosBottomRight().x && this->getPosBottomRight().x+mv > r.getPosBottomRight().x){
    std::cout<< "l" << std::endl;
    return 'l';
  }
}


bool Character::isCollision(std::vector<Rectangle> list, glm::vec2 dir){
  for(int i = 0; i<list.size(); i++){
    if(collision(list[i], dir)){
      return true;
    }
  }
  return false;
}

void Character::setPositionX(float newPos){
  this->topLeft.x = newPos;
}

void Character::setPositionY(float newPos){
  
  this->topLeft.y = newPos;
}

int Character::setPositionIfCollision(Rectangle r, float mv, int direction){
  int coll = 0;

  if(this->whereIsCollision(r, mv) == 'u' && direction ==0){
    coll = 1;
    setPositionY(r.getPosBottomRight().y);
  }
  else if(this->whereIsCollision(r, mv) == 'd' && direction ==1){
    coll = 1;
    setPositionY(r.getPosUpperLeft().y+getHeight());
  }
  else if(this->whereIsCollision(r, mv) == 'r' && direction ==2){
    coll = 1;
    setPositionX(r.getPosUpperLeft().x-getWidth());
  }
  else if(this->whereIsCollision(r, mv) == 'l' && direction ==3){
    coll = 1;
    setPositionX(r.getPosBottomRight().x);
  }

  return coll;
}