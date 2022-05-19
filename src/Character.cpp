#include "Character.h"
#include "glad/glad.h"
#include <stdlib.h>

Character::Character(){}

Character::Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee): Rectangle(posTL,posBR,col){
  this->positionArrivee = positionArrivee;
  this->velocity = {0,0};
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


bool Character::collision(Rectangle r, glm::vec2 dir){
    if(((dir.x+getWidth()) > r.getPosUpperLeft().x)
    && (dir.x < r.getPosBottomRight().x)
    && ((dir.y-getHeight()) < r.getPosUpperLeft().y)
    && (dir.y > r.getPosBottomRight().y)){
      return true;
    }
    return false;

}

float Character::collisionHorizontal(Rectangle r, glm::vec2 nextMove){
  if(nextMove.y < r.getPosUpperLeft().y && (nextMove.y+getHeight()) > r.getPosBottomRight().y){
      //collision character left
      if(nextMove.x+getWidth() > r.getPosBottomLeft().x && nextMove.x+getWidth() > r.getPosBottomRight().x){
        return r.getPosBottomRight().x;
      }
      //collision character right
      if(nextMove.x+getWidth() < r.getPosBottomRight().x && nextMove.x+getWidth() > r.getPosBottomLeft().x){
        return r.getPosBottomLeft().x-getWidth();

      }
  }
  return nextMove.x;
}

float Character::collisionVertical(Rectangle r, glm::vec2 nextMove){

    if(nextMove.x+getWidth() < r.getPosUpperRight().x && nextMove.x > r.getPosBottomLeft().x){
        //collision character bottom
        if(((nextMove.y-getHeight()) < r.getPosUpperLeft().y) && ((nextMove.y -getHeight()) > r.getPosBottomLeft().y)){
          return r.getPosUpperLeft().y+getHeight();
        }
        if((nextMove.y > r.getPosBottomLeft().y) && (nextMove.y < r.getPosUpperLeft().y)){
          return r.getPosBottomLeft().y;
        }
    }
    return nextMove.y;


}

void Character::mouvments(glm::vec2 acc){
  velocity.x += acc.x;
  velocity.y += acc.y;
  this->topLeft.x += velocity.x;
  this->topLeft.y += velocity.y;

  velocity.x = 0.5*velocity.x;
  velocity.y = 0.9*velocity.y;
}

glm::vec2 Character::getValMouvments(glm::vec2 acc){
  float velx = velocity.x +acc.x;
  float vely = velocity.y +acc.y;
  return glm::vec2 (this->topLeft.x+velx, this->topLeft.y+vely);
}

void Character::setPositionX(float newPos){
  this->topLeft.x = newPos;
}

void Character::setPositionY(float newPos){
  this->topLeft.y = newPos;
}
