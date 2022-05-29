#ifndef CHARACTER_H
#define CHARACTER_H

#include "Rectangle.h"
#include <vector>


class Character : public Rectangle {
  private : // récupère les mêmes attributs et fonctions que dans Rectangle
    glm::vec2 positionArrivee;
    float jumpPower;




  public:
    glm::vec2 velocity;
    float acceleration;
    glm::vec2 getPosFinal();
    float getJumpPower();
    void drawFinalPos();
    bool isInFinalPos();
    void setFinalPos();
    void reduceVelocity();

    Character();
    Character(glm::vec2 posTL, glm::vec2 posBR, glm::vec3 col, glm::vec2 positionArrivee,float jumpPower);
    void displayValues();

    bool collision(Rectangle r, glm::vec2 dir);
    bool inCollision(std::vector<Rectangle> listR,glm::vec2 dir);
    glm::vec2 getValMouvments(glm::vec2 acc);


    void setPositionX(float newPos);
    void setPositionY(float newPos);
    void mouvments(glm::vec2 acc, float deltaTime);
    float collisionHorizontal(Rectangle r, glm::vec2 nextMove);
    float collisionVertical(Rectangle r, glm::vec2 nextMove);


};

#endif //CHARACTER_H
